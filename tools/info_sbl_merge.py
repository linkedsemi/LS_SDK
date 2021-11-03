import sys
import os
from intelhex import IntelHex
import struct
import zlib

fh_i = open(sys.argv[1],'rb')
ic = sys.argv[2]
sbl_data = fh_i.read()
test_word0 = 0xa5a53c3c
test_word1 = 0x5a5ac3c3
if ic == 'le501x':
    flash_base = 0x18000000
    cap_delay = 2
    spi_clk = 0
    cfg_info = 0xffffffbf
    image_crypt = 0xffffffff
    sbl_code_start = 0x18000300
    sbl_code_length = len(sbl_data)
    data_storage_base = 0x18002000
    data_storage_size = 0x3000
    assert(data_storage_base >= sbl_code_start + sbl_code_length)
    app_image_base = 0x18005000
    assert(app_image_base >= data_storage_base + data_storage_size)
    fota_image_base = 0x1803d000
    crc_rslt = zlib.crc32(sbl_data)
    crc_bytes = struct.pack("I",crc_rslt)
    sbl_data = sbl_data + crc_bytes
    info_head = struct.pack('IIHHIIIIIIIII',test_word0,test_word1,cap_delay,spi_clk,cfg_info,image_crypt,0xffffffff,0xffffffff,sbl_code_start,sbl_code_length,app_image_base,fota_image_base,data_storage_base)
elif ic== 'sagi' :
    flash_base = 0x00800000
    code_offset = 0x1000
    sbl_code_length = len(sbl_data)
    sbl_code_start = flash_base+code_offset
    sbl_code_exec_addr = 0x401000
    feature_mask = 0xffffffff
    data_storage_base = 0x802000
    data_storage_size = 0x3000
    assert(data_storage_base >= sbl_code_start + sbl_code_length)
    app_image_base = 0x805000
    assert(app_image_base >= data_storage_base + data_storage_size)
    fota_image_base = 0x83d000
    info_head = struct.pack('IIIIIIIII',test_word0,test_word1,code_offset,sbl_code_length,sbl_code_exec_addr,feature_mask,data_storage_base,app_image_base,fota_image_base)  
elif ic== 'gemini' :
    flash_base = 0x00800000
    code_offset = 0x1000
    sbl_code_length = len(sbl_data)
    feature_mask = 0xffffffff
    sbl_crc_rslt = zlib.crc32(sbl_data)
    sbl_crc = struct.pack('I',sbl_crc_rslt)
    sbl_data=sbl_data+sbl_crc
    sbl_code_start = flash_base+code_offset
    sbl_code_exec_addr = 0x20001000
    uart_cmd_mask = 0xffffffff
    # feature_mask = 0xfffd0002
    crc_data = struct.pack('IIIIIII',test_word0,test_word1,code_offset,sbl_code_length,sbl_code_exec_addr,uart_cmd_mask,feature_mask)
    crc_rslt = zlib.crc32(crc_data)
    data_storage_base = 0x802000
    data_storage_size = 0x3000
    assert(data_storage_base >= sbl_code_start + sbl_code_length)
    app_image_base = 0x805000
    assert(app_image_base >= data_storage_base + data_storage_size)
    fota_image_base = 0x83d000
    info_head = struct.pack('IIIIIIIIIII',test_word0,test_word1,code_offset,sbl_code_length,sbl_code_exec_addr,uart_cmd_mask,feature_mask,crc_rslt,data_storage_base,app_image_base,fota_image_base)  

mac_addr_base = flash_base + 0x30
mac_addr = bytes([0xff,0xff,0xff,0xff,0xff,0xff]) # ff:ff:ff:ff:ff:ff is not a valid address

ih = IntelHex()
ih.puts(flash_base,info_head)
ih.puts(mac_addr_base,mac_addr)
ih.puts(sbl_code_start,sbl_data)
ih.write_hex_file(sys.argv[3])

