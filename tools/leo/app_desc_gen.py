import sys
import struct
import zlib
from ecdsa import SigningKey
import hashlib

SBL_LEN_OFFSET = 12
FEATUERE_MASK_OFFSET = 24
HEADER_CRC_OFFSET = 0x24 # 内部flash最后的crc
APP_DESC_OFFSET = 0x4000 # app在bin文件中的偏移
APP_SIGN_LEN = 64
IMAGE_OFFSET = 0x4020
APP_OFFSET = 0x4070
APP_SIGN_OFFSET = APP_OFFSET - 0x40
APP_SIZE_OFFSET = APP_OFFSET - 0x44
SBL_IMAGE_OFFSET = 0x100
INFO_SBL_DATA_LEN = 0x2000
INFO_SBL_DATA_LEN_OFFSET = 20
INFO_SBL_DATA_CRC32_OFFSET = 28
PUBLIC_KEY_OFFSET = 0x40
INFO_SBL_OFFSET = 0x30  #info_sbl在bios文件中的偏移
app_magic = b'LSEC_APP'
IMAGE_OFFSET_IN_BIOS_FILE = IMAGE_OFFSET + INFO_SBL_OFFSET
SECURE_BOOT_ENABLED = 1
SECP256K1_USED = 0

# 检查输入参数数量
if len(sys.argv) < 5:
    print("Usage: python app_desc_gen.py <app_firmware_file> <bios_template_file>")
    sys.exit(1)

app_firmware = sys.argv[1]
bios_file = sys.argv[2]
public_key_file = sys.argv[3]
private_key_file = sys.argv[4]
curv_type = sys.argv[5]
if curv_type == "secp256k1":
    SECP256K1_USED = 1
else:
    SECP256K1_USED = 0
print("SECP256K1_USED :",SECP256K1_USED)

output_app_bin = "secure_boot_app.bin"
output_bios_file =  "secure_boot_bios.bin"

# 读取app固件
try:
    with open(app_firmware, 'rb') as fw_bin:
        fw_data = bytearray(fw_bin.read())
except IOError:
    print(f"Error: Could not open app firmware file: {app_firmware}")
    sys.exit(1)

# 读取公钥文件
try:
    with open(public_key_file, 'rb') as pubkey_bin:
        pubkey_data = pubkey_bin.read()
except IOError:
    print(f"Error: Could not open public key file: {public_key_file}")
    sys.exit(1)
pk_file_len = len(pubkey_data)

# 读取私钥文件
try:
    with open(private_key_file, 'rb') as prikey_bin:
        prikey_data = prikey_bin.read()
except IOError:
    print(f"Error: Could not open private key file: {private_key_file}")
    sys.exit(1)
sk = SigningKey.from_pem(prikey_data)


old_feature_mask = struct.unpack('I', fw_data[FEATUERE_MASK_OFFSET:FEATUERE_MASK_OFFSET+4])[0]
new_feature_mask = (old_feature_mask|SECURE_BOOT_ENABLED<<1|SECP256K1_USED<<2) & ~((SECURE_BOOT_ENABLED<<1|SECP256K1_USED<<2) << 16)
new_feature_mask_bytes = struct.pack('I', new_feature_mask)
# 更新头部feature_mask
fw_data[FEATUERE_MASK_OFFSET: FEATUERE_MASK_OFFSET + 4] = new_feature_mask_bytes
head_crc = zlib.crc32(fw_data[0: HEADER_CRC_OFFSET])
new_head_crc_bytes = struct.pack('I', head_crc)
# 更新头部crc
fw_data[HEADER_CRC_OFFSET : HEADER_CRC_OFFSET + 4] = new_head_crc_bytes
# 添加公钥到偏移0x40的位置
fw_data[PUBLIC_KEY_OFFSET: PUBLIC_KEY_OFFSET + pk_file_len] = pubkey_data

sbl_len_bytes  = fw_data[SBL_LEN_OFFSET:SBL_LEN_OFFSET + 4]
sbl_len = struct.unpack('I', sbl_len_bytes)[0] #解包为无符号整数
print("sbl_len :",sbl_len)

sbl_data = fw_data[SBL_IMAGE_OFFSET: SBL_IMAGE_OFFSET + sbl_len]
sbl_signature = sk.sign_deterministic(sbl_data,hashfunc = hashlib.sha256)
# 添加sbl_data的签名到sbl_data的后面
fw_data[SBL_IMAGE_OFFSET+sbl_len : SBL_IMAGE_OFFSET+sbl_len + APP_SIGN_LEN] = sbl_signature

app_data = fw_data[APP_OFFSET:] # 从固件中提取应用部分
app_data_len = len(app_data)
app_version = 0x1
app_signature = sk.sign_deterministic(app_data,hashfunc = hashlib.sha256) 
print("app_data_len :",app_data_len)
# 添加app_data的签名
fw_data[APP_SIGN_OFFSET : APP_SIGN_OFFSET + APP_SIGN_LEN] = app_signature
app_data_len_bytes = struct.pack('I', app_data_len)
fw_data[APP_SIZE_OFFSET : APP_SIZE_OFFSET + 4] = app_data_len_bytes

image_data = fw_data[IMAGE_OFFSET:] # 从固件中提取整个image
image_size = len(image_data)
image_crc32 = zlib.crc32(image_data)
app_desc_head = struct.pack('8sIIII', app_magic, IMAGE_OFFSET_IN_BIOS_FILE, image_size, app_version, image_crc32)
app_desc_crc_val = zlib.crc32(app_desc_head)
print("app_desc_crc_val",app_desc_crc_val)
app_desc_crc = struct.pack('I', app_desc_crc_val)

# app的头部
app_image_header = app_desc_head + app_desc_crc
app_image_header_len = len(app_image_header)
print(f"App Description Header + CRC length: {app_image_header_len} bytes")
# 添加app的header
fw_data[APP_DESC_OFFSET : APP_DESC_OFFSET + app_image_header_len] = app_image_header


# --- 2. 处理 BIOS 文件 (读取并修改) ---
try:
    with open(bios_file, 'rb') as fw_bios:
        fw_bios_bin = bytearray(fw_bios.read()) # 使用 bytearray 可变字节序列
except IOError:
    print(f"Error: Could not open BIOS template file: {bios_file}")
    sys.exit(1)

fw_bios_bin_len = len(fw_bios_bin)
print(f"Original BIOS file length: {fw_bios_bin_len} bytes")
print(f"Target write offset in BIOS: 0x{APP_DESC_OFFSET:X}")


try:
    with open(output_app_bin, 'wb') as app_out:
        app_out.write(fw_data)
    print(f"Successfully wrote data to {output_app_bin}.")
except IOError:
    print(f"Error: Could not write file: {output_app_bin}")
    sys.exit(1)
fw_data_len = len(fw_data)

# 更新bios文件中mirror文件的大小和crc
info_sbl_data = fw_data[:INFO_SBL_DATA_LEN]
info_sbl_crc32 = zlib.crc32(info_sbl_data)
info_sbl_crc32_bytes = struct.pack('I', info_sbl_crc32)
info_sbl_data_len = struct.pack('I', INFO_SBL_DATA_LEN)
fw_bios_bin[INFO_SBL_DATA_LEN_OFFSET : INFO_SBL_DATA_LEN_OFFSET + 4] = info_sbl_data_len
fw_bios_bin[INFO_SBL_DATA_CRC32_OFFSET : INFO_SBL_DATA_CRC32_OFFSET + 4] = info_sbl_crc32_bytes

ext_flash_image_desc = fw_bios_bin[0x10:0x10+28]
ext_flash_image_desc_crc32 = zlib.crc32(ext_flash_image_desc)
ext_flash_image_desc_crc32_bytes = struct.pack('I', ext_flash_image_desc_crc32)
fw_bios_bin[44:44+4] = ext_flash_image_desc_crc32_bytes

#将新的bin文件覆盖bios偏移0x30的位置 ---
fw_bios_bin[INFO_SBL_OFFSET : INFO_SBL_OFFSET + fw_data_len] = fw_data
try:
    with open(output_bios_file, 'wb') as f_bios_out:
        f_bios_out.write(fw_bios_bin)
    print(f"Successfully wrote data to {output_bios_file} at offset 0x{INFO_SBL_OFFSET:X}. File updated.")
except IOError:
    print(f"Error: Could not write to output BIOS file: {output_bios_file}")
    sys.exit(1)