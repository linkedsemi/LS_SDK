import sys
import struct
import zlib
import os

COPY_TO_RAM = 0
FLASH_CHIP_ERASE = 1
RAM_DST_ADDR = 0x0
RAM_ENTRY_ADDR = 0x0
PADDING_ENABLE = 0x1

split_ptr = not (len(sys.argv) == 2)
if split_ptr:
    desc_offset = int(sys.argv[2],16)
else:
    desc_offset = 0x10

magic = b'LSEC'
int_flash_search_loop = 0x0
int_flash_search_delay_10us = 0x0
desc_ptr_head = struct.pack('4sIHH',magic,desc_offset,int_flash_search_loop,int_flash_search_delay_10us)
desc_ptr_crc = struct.pack('I',zlib.crc32(desc_ptr_head))

fw_bin = open(sys.argv[1],'rb')
name = os.path.basename(sys.argv[1]).split('.')[0]
output_dir = os.path.dirname(sys.argv[1])
fw_data = fw_bin.read()
image_version = int.from_bytes(fw_data[0x1c:0x20],'little')
fw_len = len(fw_data)
fw_crc32 = zlib.crc32(fw_data)
image_offset = 0x20
copy_strategy = FLASH_CHIP_ERASE<<1|COPY_TO_RAM
desc_head = struct.pack('IIIIIII',image_offset,fw_len,image_version,fw_crc32,copy_strategy,RAM_DST_ADDR,RAM_ENTRY_ADDR)
desc_crc = struct.pack('I',zlib.crc32(desc_head))

if split_ptr:
    f_ptr = open(os.path.join(output_dir,name+'_ec_firmware_pointer_into.bios'),'wb')
    f_ptr.write(desc_ptr_head)
    f_ptr.write(desc_ptr_crc)
    f_ptr.close()
    f_desc_fw = open(os.path.join(output_dir,name+'_ec_into.bios'),'wb')
    f_desc_fw.write(desc_head)
    f_desc_fw.write(desc_crc)
    f_desc_fw.write(fw_data)
    f_desc_fw.close()
else:
    f_total = open(os.path.join(output_dir,name+'_ec_into.bios'),'wb')
    f_total.write(desc_ptr_head)
    f_total.write(desc_ptr_crc)
    f_total.write(desc_head)
    f_total.write(desc_crc)
    f_total.write(fw_data)
    f_total.close()

if PADDING_ENABLE:
    base_size = 128*1024
    padding_file = open(os.path.join(output_dir,name+'_ec_into.bios'),'ab')
    file_size = os.path.getsize(padding_file.name)
    
    if 0 < file_size < base_size:
        target_size = base_size*1
    elif base_size < file_size < base_size*2:
        target_size = base_size*2
    elif base_size*2 < file_size < base_size*4:
        target_size = base_size*4
    else:
        target_size = 0

    if target_size:
        padding_size = target_size - file_size
        padding_file.write(bytes([0xFF] * padding_size))

    padding_file.close()