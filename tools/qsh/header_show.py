import sys
import struct

def usage():
    print("usage: ")
    print("    python {} <img_input.bin>".format(sys.argv[0]))

if len(sys.argv) != 2:
    usage()
    sys.exit()

_path_input = sys.argv[1]

image_header_format = (
    '<'            # little-endian
    '2I'           # test_word[2]
    'I'            # offset
    'I'            # length
    'I'            # version
    'B'            # arg0
    'B'            # arg1
    'B'            # arg2
    'B'            # arg3
    '16s'          # arg4[0x10]
    '144s'         # arg5[0x90]
    '64s'          # arg6[0x40]
    'I'            # exe_addr
    'I'            # header_crc
)

header_size = struct.calcsize(image_header_format)

with open(_path_input, 'rb') as f:
    data = f.read(header_size)
    fields = struct.unpack(image_header_format, data)

print("test_word[0]:", hex(fields[0]))
print("test_word[1]:", hex(fields[1]))
print("offset:", hex(fields[2]))
print("length:", hex(fields[3]))
print("version:", hex(fields[4]))
print("exe_addr:", hex(fields[12]))
print("header_crc:", hex(fields[13]))
