from ecdsa import SigningKey, NIST256p
from intelhex import IntelHex
import sys
import shutil
import hashlib
import subprocess
import struct
import zlib
import os
import base64

FEATUERE_MASK_OFFSET = 24
SBL_LEN_OFFSET = 12
VK_STR_OFFSET = 0x40
SBL_OFFSET = 0X80

def save_to_file(file_name, contents):
    fh = open(file_name, 'wb')
    fh.write(contents)
    fh.close()

def load_file(file_name):
    fh = open(file_name,'rb')
    return fh.read()

def bytes_to_hex_string(data):
    return " ".join(format(byte, "02x") for byte in data)

# sys.argv[1] ：ic=leo or ic=lm3050
# sys.argv[2] ：[firmware].bin
# sys.argv[3] : vk_string.bin
# sys.argv[4] : sk_pem.pem
# sys.argv[5] : secp256r1 or secp256k1 : curv type

if sys.argv[1] == "ic=lm3050":
    print("ic=lm3050")
    HEADER_CRC_OFFSET = 0x1c
    APP_ADD = 0X500
    FLASH_BASE_ADD = 0X800000
elif sys.argv[1] == "ic=leo":
    print("ic=leo")
    HEADER_CRC_OFFSET = 0x24
    APP_ADD = 0X800
    FLASH_BASE_ADD = 0X8000000
else:
    print("Invalid IC,Use ic=lm3050 or ic=leo")

APP_SIGN_ADD = APP_ADD-64

with open(sys.argv[2],'rb') as info_bin:
    firmware_bin = info_bin.read()


if sys.argv[5] == "secp256k1":
    SECP256K1_USED = 1
    print("curv type = secp256k1")
else:
    SECP256K1_USED = 0
    print("curv type = secp256r1")

SECURE_BOOT_ENABLED = 1
feature_mask_offset = FEATUERE_MASK_OFFSET 
feature_mask = struct.unpack('I', firmware_bin[feature_mask_offset:feature_mask_offset+4])[0]
new_feature_mask = (feature_mask|SECURE_BOOT_ENABLED<<1|SECP256K1_USED<<2) & ~((SECURE_BOOT_ENABLED<<1|SECP256K1_USED<<2) << 16)
new_feature_mask_bytes = struct.pack('I', new_feature_mask)
firmware_bin = (firmware_bin[:feature_mask_offset] + new_feature_mask_bytes + firmware_bin[feature_mask_offset+4:])
# print(firmware_bin)

head_crc_offset = HEADER_CRC_OFFSET
head_crc = zlib.crc32(firmware_bin[:head_crc_offset])
new_head_crc_bytes = struct.pack('I', head_crc)
firmware_bin = (firmware_bin[:head_crc_offset] + new_head_crc_bytes + firmware_bin[head_crc_offset+4:])
# print(firmware_bin)

vk_string_offset = VK_STR_OFFSET
with open(sys.argv[3],'rb') as vk_bin:
    vk_string = vk_bin.read()
# vk_string_bytes = struct.pack('64B', vk_string)
firmware_bin = (firmware_bin[:vk_string_offset] + vk_string + firmware_bin[vk_string_offset+64:])



sbl_offset = SBL_OFFSET
sbl_len_bytes  = firmware_bin[SBL_LEN_OFFSET:SBL_LEN_OFFSET+4]
sbl_len = struct.unpack('I', sbl_len_bytes)[0]
print("sbl_len :",sbl_len)
sbl_data = firmware_bin[sbl_offset:sbl_len+sbl_offset]
with open(sys.argv[4],'rb') as sk_file:
    sk_pem = sk_file.read()
sk = SigningKey.from_pem(sk_pem)
sbl_signature = sk.sign_deterministic(sbl_data,hashfunc = hashlib.sha256)
firmware_bin = (firmware_bin[:sbl_offset+sbl_len] + sbl_signature + firmware_bin[sbl_offset+sbl_len+64:])


app_bin = firmware_bin[APP_ADD:]
app_len = len(app_bin)
app_signature = sk.sign_deterministic(app_bin,hashfunc = hashlib.sha256)
print("app_len :",app_len)
firmware_bin = (firmware_bin[:APP_SIGN_ADD] + app_signature + firmware_bin[APP_SIGN_ADD+64:])
app_len_bytes = struct.pack('I', app_len)
firmware_bin = (firmware_bin[:APP_SIGN_ADD-4] + app_len_bytes + firmware_bin[APP_SIGN_ADD:])

# save_to_file('output_bin.bin', firmware_bin)

ih = IntelHex()
ih.puts(FLASH_BASE_ADD,firmware_bin)
ih.write_hex_file(sys.argv[2]+'_signature.hex')
print(sys.argv[2]+'_signature.hex')