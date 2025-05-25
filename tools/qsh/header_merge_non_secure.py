import sys
import os
import getopt
import struct
import zlib

def usage():
    print("usage: ")
    print("    python {} -i <img_input.bin> -o <img_with_header_output.bin> -a <exe_addr_hex>".format(sys.argv[0]))
    print("options:")
    print("  -h, --help       show this help message")
    print("  -v, --version    show version")
    print("  -a, --address    execution address (hex)")
    print("  -i, --ifilename  input filename")
    print("  -o, --ofilename  output filename")

_exe_addr = 0
_ifilename = ""
_ofilename = ""

opts, args = getopt.getopt(sys.argv[1:], 'hva:i:o:', ['help','version','address=','ifilename=','ofilename='])
for opt_name, opt_value in opts:
    # print(opt_name)
    if opt_name in ('-h','--help'):
        usage()
        exit()
    if opt_name in ('-v','--version'):
        print("Version is 0.01 ")
        exit()
    if opt_name in ('-a','--address'):
        _exe_addr = int(opt_value, 16)
        # print("execute address: ", hex(_exe_addr))
    if opt_name in ('-i','--ifilename'):
        _ifilename = opt_value
        # print("input filename is ", _ifilename)
    if opt_name in ('-o','--ofilename'):
        _ofilename = opt_value
        # print("output filename is ", _ofilename)

if not os.path.exists(_ifilename):
    print(sys.argv)
    print("input file: \"{}\" not exist".format(_ifilename))
    usage()
    exit()

image_data = open(_ifilename,'rb').read()

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
with open(_ofilename,'wb') as out:
    out.write(image_header)
    out.write(image_data)
    out.close()
