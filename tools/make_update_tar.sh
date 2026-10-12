#!/usr/bin/env bash
# Generate OpenBMC firmware update packages
# (MANIFEST + time + image-bmc + image-rofs) from the current build outputs,
# ready to drop into /SD2/images (or upload via bmcweb). Two packages are
# produced, both from the same ustar stream:
#   obmc-image-<machine>-<version>.tar     plain, for the Web UI / a slot whose
#                                          firmware was built without gzip
#   obmc-image-<machine>-<version>.tar.gz  gzipped, the normal upload (the
#                                          device inflates it with miniz tinfl)
# Keeping both in firmware_update from the same build is deliberate: a stale
# .tar left behind silently reflashes the "other" A/B slot with an older app
# (that is how a slot ended up without gzip support and rejected every .tar.gz
# with "Invalid size field").
# Runs standalone or as a CMake post-build step (see
# modules/hal/linkedsemi/zephyr/CMakeLists.txt, target "openbmc_update_tar").
#
# Usage: make_update_tar.sh [version] [machine]
#   version  MANIFEST version field           (default: v1.1.0)
#   machine  MANIFEST MachineName/Compatible  (default: lsqsh_evb)
#
# All paths are supplied by the CMake target "openbmc_update_tar" (a west build
# does not live in ${WS_ROOT}/build):
#   UPDATE_TAR_APP_BIN    app flash image
#   UPDATE_TAR_ROFS_BIN   rofs image
#   UPDATE_TAR_OUT_DIR    output directory
set -euo pipefail

VERSION="${1:-${UPDATE_TAR_VERSION:-v1.1.0}}"
MACHINE="${2:-${UPDATE_TAR_MACHINE:-lsqsh_evb}}"

APP_BIN="${UPDATE_TAR_APP_BIN}"
ROFS_BIN="${UPDATE_TAR_ROFS_BIN}"
OUT_DIR="${UPDATE_TAR_OUT_DIR}"

for f in "${APP_BIN}" "${ROFS_BIN}"; do
    if [ ! -f "${f}" ]; then
        echo "make_update_tar: missing ${f} -- build the app first" >&2
        exit 1
    fi
done

PKG="${OUT_DIR}/pkg"
mkdir -p "${PKG}"
cp "${APP_BIN}" "${PKG}/image-bmc"
cp "${ROFS_BIN}" "${PKG}/image-rofs"

cat > "${PKG}/MANIFEST" <<EOF
purpose=xyz.openbmc_project.Software.Version.VersionPurpose.BMC
version=${VERSION}
MachineName=${MACHINE}
ExtendedVersion=dualslot-app-rofs
CompatibleName=${MACHINE}
EOF

# Build time of this package. It travels inside the archive on purpose: the
# device extracts every member, and an image directory there is named after the
# image's content hash, which says nothing about age. With this file
#   cat /mnt/images/<id>/time
# tells you which image is the new one and which is the older one -- no BMC code
# has to know anything about it.
date +"%Y-%m-%dT%H:%M:%SZ" > "${PKG}/time"

TAR="${OUT_DIR}/obmc-image-${MACHINE}-${VERSION}.tar"
TAR_GZ="${OUT_DIR}/obmc-image-${MACHINE}-${VERSION}.tar.gz"

# One ustar stream, written to disk first so both packages are byte-identical
# in content (the device accepts either path, see
# phosphor-bmc-code-mgt/image_manager.cpp).
tar --format=ustar -C "${PKG}" -cf "${TAR}" MANIFEST time image-bmc image-rofs

# gzip the same stream: the upload transfer dominates update time on the BMC,
# and the device inflates it on the fly (miniz tinfl). -n keeps the output
# reproducible (no name/timestamp in the gzip header).
gzip -9n -c "${TAR}" >"${TAR_GZ}"

echo "make_update_tar: ${TAR} ($(du -h "${TAR}" | cut -f1))"
echo "make_update_tar: ${TAR_GZ} ($(du -h "${TAR_GZ}" | cut -f1))"
