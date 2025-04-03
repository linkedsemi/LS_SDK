import sys
import struct
import zlib
from gmssl import sm2
from gmssl.sm4 import CryptSM4, SM4_ENCRYPT
from binascii import unhexlify, hexlify

do_sign = True
do_crypt = True
do_kek = True
# if 'sign' in sys.argv:
#     do_sign = True
# if 'crypt' in sys.argv:
#     do_crypt = True
# if 'kek' in sys.argv:
#     do_kek = True

CRYPT_PRI_KEY = 'B9AB0B828FF68872F21A837FC303668428DEA11DCD1B24429D0C99E24EED83D5'
CRYPT_PUB_KEY = 'B9C9A6E04E9C91F7BA880429273747D7EF5DDEB0BB2FF6317EB00BEF331A83081A6994B8993F3F5D6EADDDB81872266C87C018FB4162F5AF347B483E24620207'
SIGN_PRI_KEY = 'B9AB0B828FF68872F21A837FC303668428DEA11DCD1B24429D0C99E24EED83D5'
SIGN_PUB_KEY = 'B9C9A6E04E9C91F7BA880429273747D7EF5DDEB0BB2FF6317EB00BEF331A83081A6994B8993F3F5D6EADDDB81872266C87C018FB4162F5AF347B483E24620207'
SM4_KEY = 0x67f1aec5ba0d615be0c7074923de30ba
IV = 0xf0f1f2f3f4f5f6f7f8f9fafb

def image_sign(data, pri_key, pub_key):
    sm2_local = sm2.CryptSM2(pri_key, pub_key, mode=1)
    return sm2_local.sign_with_sm3(data)

def sm2_kek(key, pri_key, pub_key):
    sm2_local = sm2.CryptSM2(pri_key, pub_key, mode=1)
    return sm2_local.encrypt(key)

def sm4_ctr_encrypt(data,key,_ctr_cnt):
    crypt_sm4 = CryptSM4(padding_mode=1)
    crypt_sm4.set_key(key, SM4_ENCRYPT)
    _cnt= int.from_bytes(_ctr_cnt)
    _len = len(data)
    out_data=b''
    index = 0
    while _len > 0 :
        rs = crypt_sm4.crypt_ecb(_cnt.to_bytes(16, 'big'))[:0x10]
        for a,b in zip(data[index:index+16], rs) :
            out_data += (a ^ b).to_bytes()
        index += 16
        _cnt += 1
        _len -= 16
    return out_data

sign_pri_key = SIGN_PRI_KEY
sign_pub_key = SIGN_PUB_KEY
crypt_pri_key = CRYPT_PRI_KEY
crypt_pub_key = CRYPT_PUB_KEY
sm4_key = SM4_KEY.to_bytes(16,'big')
iv = IV.to_bytes(12,'big')
image_data = open(sys.argv[1],'rb').read()

test_word0              = 0xa5a53c3c
test_word1              = 0x5a5ac3c3
offset                  = 0x100
length                  = len(image_data)
version                 = 0x1
decrypt_key_id          = 0
public_key_id           = 0
kek_enable              = 0 
exe_addr                = 0x0
count                   = [0xFF] * 16
realtime_decrypt_lock   = 0
sign                    = [0xFF] * 64
encrypt_key             = [0xFF] * 144

if do_crypt:
    decrypt_key_id = 1
    count = iv + struct.pack('>I', offset >> 4)
    image_data = sm4_ctr_encrypt(image_data, sm4_key, count)
    if do_kek:
        kek_enable = 1
        decrypt_key_id = 2
        encrypt_key = sm2_kek(sm4_key, crypt_pri_key, crypt_pub_key) + b'\xFF' * 32
if do_sign:
    public_key_id = 3
    sign = unhexlify(image_sign(image_data, sign_pri_key, sign_pub_key))
    print(f'firmware_sign: 0x{sign.hex()}')

image_header  = struct.pack('5I', test_word0, test_word1, offset, length, version)
image_header += struct.pack('4B', decrypt_key_id, public_key_id, kek_enable, realtime_decrypt_lock)
image_header += struct.pack('16B', *count)
image_header += struct.pack('144B', *encrypt_key)
image_header += struct.pack('64B', *sign)
image_header += struct.pack('I', exe_addr)
image_header += struct.pack('I', zlib.crc32(image_header))
with open(sys.argv[2],'wb') as out:
    out.write(image_header)
    out.write(image_data)
    out.close()
