import sys
from intelhex import IntelHex
import struct
import zlib

fh_i = open(sys.argv[1],'rb')
app_base = sys.argv[2]
sbl_data = fh_i.read()
test_word0 = 0xa5a53c3c
test_word1 = 0x5a5ac3c3
flash_base = 0x18000000
cap_delay = 2
spi_clk = 0
cfg_info = 0xffffffbf
image_crypt = 0xffffffff
sbl_code_start = 0x18000300
sbl_code_length = len(sbl_data)
assert(0x18002000 >= sbl_code_start + sbl_code_length)
data_storage_base = 0x1807C000
app_image_base = int(app_base)
crc_rslt = zlib.crc32(sbl_data)
crc_bytes = struct.pack("I",crc_rslt)
sbl_data = sbl_data + crc_bytes
info_head = struct.pack('IIHHIIIIIIIII',test_word0,test_word1,cap_delay,spi_clk,cfg_info,image_crypt,0xffffffff,0xffffffff,sbl_code_start,sbl_code_length,app_image_base,0xffffffff,data_storage_base)

mac_addr_base = flash_base + 0x30
mac_addr = bytes([0xff,0xff,0xff,0xff,0xff,0xff]) # ff:ff:ff:ff:ff:ff is not a valid address

ih = IntelHex()
ih.puts(flash_base,info_head)
ih.puts(mac_addr_base,mac_addr)
ih.puts(sbl_code_start,sbl_data)
ih.write_hex_file(sys.argv[3])

