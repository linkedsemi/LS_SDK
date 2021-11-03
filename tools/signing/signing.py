from ecdsa import SigningKey, NIST256p
import sys
import shutil
import hashlib
import subprocess
import os

def save_to_file(file_name, contents):
    fh = open(file_name, 'wb')
    fh.write(contents)
    fh.close()

def load_file(file_name):
    fh = open(file_name,'rb')
    return fh.read()

sk_pem = load_file(sys.argv[2])
sk = SigningKey.from_pem(sk_pem)

message = load_file(sys.argv[1])
signature = sk.sign_deterministic(message,hashfunc = hashlib.sha256)
save_to_file('signature.bin',signature)
