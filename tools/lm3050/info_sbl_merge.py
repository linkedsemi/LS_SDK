import sys
import struct
import zlib
# Feature
DEBUG_PORT_DISABLED = 0
SECURE_BOOT_ENABLED = 0
SECP256K1_USED = 0

UART_CMD_MASK = 0xffffffff

sbl_file = open(sys.argv[1],'rb')
sbl_data = sbl_file.read()
test_word0 = 0xa5a53c3c
test_word1 = 0x5a5ac3c3
sbl_offset = 32
sbl_length = len(sbl_data)
sbl_crc = zlib.crc32(sbl_data)
sbl_crc_bytes = struct.pack("I",sbl_crc)
sbl_dst = 0x20001000
feature_mask = DEBUG_PORT_DISABLED|SECURE_BOOT_ENABLED<<1|SECP256K1_USED<<2
feature_mask = ((~feature_mask)<<16|feature_mask)&0xffffffff
info_head = struct.pack('IIIIIII',test_word0,test_word1,sbl_offset,sbl_length,sbl_dst,UART_CMD_MASK,feature_mask)
head_crc = zlib.crc32(info_head)
head_crc_bytes = struct.pack("I",head_crc)

with open(sys.argv[2],'wb') as out:
    out.write(info_head)
    out.write(head_crc_bytes)
    out.write(sbl_data)
    out.write(sbl_crc_bytes)
    out.close()
