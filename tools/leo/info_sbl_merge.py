import sys
import struct
import zlib
# Feature
DEBUG_PORT_DISABLED = 0
SECURE_BOOT_ENABLED = 0
SECP256K1_USED = 0

UART_CMD_MASK = 0xffffffff

PUBLIC_KEY_END_OFFSET = 128
SBL_IMAGE_OFFSET = 0x100
APP_DESC_OFFSET = 0x2000

sbl_file = open(sys.argv[1],'rb')
sbl_data = sbl_file.read()
test_word0 = 0xa5a53c3c
test_word1 = 0x5a5ac3c3
sbl_offset = SBL_IMAGE_OFFSET
sbl_length = len(sbl_data)
sbl_crc = zlib.crc32(sbl_data)
sbl_crc_bytes = struct.pack("I",sbl_crc)
sbl_dst = 0x10001000
feature_mask = DEBUG_PORT_DISABLED|SECURE_BOOT_ENABLED<<1|SECP256K1_USED<<2
feature_mask = ((~feature_mask)<<16|feature_mask)&0xffffffff
image_version = 0x00000001
search_cfg = 0x00000000
info_head = struct.pack('IIIIIIIII',test_word0,test_word1,sbl_offset,sbl_length,sbl_dst,UART_CMD_MASK,feature_mask,image_version,search_cfg)
head_crc = zlib.crc32(info_head)
head_crc_bytes = struct.pack("I",head_crc)

dummy_array = struct.pack('24B', *[0xff] * 24)
key_array = struct.pack('64B', *[0xff] * 64)
dummy_array2_length = SBL_IMAGE_OFFSET-PUBLIC_KEY_END_OFFSET
dummy_array2 = struct.pack(f'{dummy_array2_length}B', *[0xff] * dummy_array2_length)
dummay_array3_length = APP_DESC_OFFSET - SBL_IMAGE_OFFSET - sbl_length - 4
dummay_array3 = struct.pack(f'{dummay_array3_length}B', *[0xff] * dummay_array3_length)

with open(sys.argv[2],'wb') as out:
    out.write(info_head)
    out.write(head_crc_bytes)
    out.write(dummy_array)
    out.write(key_array)
    out.write(dummy_array2)
    out.write(sbl_data)
    out.write(sbl_crc_bytes)
    out.write(dummay_array3)
    out.close()
