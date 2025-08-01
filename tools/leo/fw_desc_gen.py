import sys
import struct
import zlib
import os
from intelhex import IntelHex

COPY_TO_RAM = 0
FLASH_CHIP_ERASE = 1
RAM_DST_ADDR = 0x0
RAM_ENTRY_ADDR = 0x0
PADDING_ENABLE = 0x1

APP_DESC_OFFSET = 0x2000 # app在bin文件中的偏移
APP_OFFSET = 0x2060
APP_SIGN_OFFSET = APP_OFFSET - 0x40
INFO_SBL_DATA_LEN = 0x2000
# 生成最终的BIN文件
fw_bin = open(sys.argv[1],'rb')
name = os.path.basename(sys.argv[1]).split('.')[0]
output_dir = os.path.dirname(sys.argv[1])
fw_data = bytearray(fw_bin.read())
app_version = 0x1
reserved = 0x0
app_magic = b'LSEC_APP'
sign_and_image_data = fw_data[APP_SIGN_OFFSET:]
sign_and_image_size = len(sign_and_image_data)
sign_and_image_crc32 = zlib.crc32(sign_and_image_data)
app_desc_head = struct.pack('8sIIIII', app_magic, sign_and_image_size, app_version, reserved, reserved, sign_and_image_crc32)
app_desc_crc_val = zlib.crc32(app_desc_head)
app_desc_crc = struct.pack('I', app_desc_crc_val)
app_image_header = app_desc_head + app_desc_crc
app_image_header_len = len(app_image_header)
# 添加app的header
fw_data[APP_DESC_OFFSET : APP_DESC_OFFSET + app_image_header_len] = app_image_header
f_total = open(os.path.join(output_dir,name+'.bin'),'wb')
f_total.write(fw_data)
f_total.close()

# 生成HEX文件
def bin_to_hex_with_intelhex(bin_file_path, hex_file_path, start_address=0x08000000):
    try:
        ih = IntelHex() 
        ih.loadbin(bin_file_path, offset=start_address)
        ih.write_hex_file(hex_file_path)
        print(f"Successfully generated HEX file: {hex_file_path}")
    except FileNotFoundError:
        print(f"Error: BIN file not found at {bin_file_path}", file=sys.stderr)
    except Exception as e:
        print(f"An unexpected error occurred during HEX conversion: {e}", file=sys.stderr)
hex_file_path = os.path.join(output_dir, name + '.hex')
final_bin_file_path = os.path.join(output_dir, name + '.bin')
bin_to_hex_with_intelhex(final_bin_file_path, hex_file_path, start_address=0x08000000)

#生成BIOS文件
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
image_version = int.from_bytes(fw_data[0x1c:0x20],'little')
info_sbl_data = fw_data[:INFO_SBL_DATA_LEN]
info_sbl_crc32 = zlib.crc32(info_sbl_data)
image_offset = 0x20
copy_strategy = FLASH_CHIP_ERASE<<1|COPY_TO_RAM
desc_head = struct.pack('IIIIIII',image_offset,INFO_SBL_DATA_LEN,image_version,info_sbl_crc32,copy_strategy,RAM_DST_ADDR,RAM_ENTRY_ADDR)
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