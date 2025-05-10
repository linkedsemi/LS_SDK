import sys
import struct
import zlib

def usage():
    print("usage: ")
    print("    python {} <img_input.bin> <img_with_header_output.bin> <exe_addr_hex>".format(sys.argv[0]))

if len(sys.argv) != 4:
    usage()
    sys.exit()

_path_input = sys.argv[1]
_path_output = sys.argv[2]
_exe_addr = int(sys.argv[3], 16)

image_data = open(_path_input,'rb').read()

test_word0              = 0xa5a53c3c
test_word1              = 0x5a5ac3c3
offset                  = 0x100
length                  = len(image_data)
version                 = 0x1
decrypt_key_id          = 0
public_key_id           = 0
kek_enable              = 0 
exe_addr                = _exe_addr
count                   = [0xFF] * 16
realtime_decrypt_lock   = 0
sign                    = [0xFF] * 64
encrypt_key             = [0xFF] * 144

image_header  = struct.pack('5I', test_word0, test_word1, offset, length, version)
image_header += struct.pack('4B', decrypt_key_id, public_key_id, kek_enable, realtime_decrypt_lock)
image_header += struct.pack('16B', *count)
image_header += struct.pack('144B', *encrypt_key)
image_header += struct.pack('64B', *sign)
image_header += struct.pack('I', exe_addr)
image_header += struct.pack('I', zlib.crc32(image_header))
with open(_path_output,'wb') as out:
    out.write(image_header)
    out.write(image_data)
    out.close()
