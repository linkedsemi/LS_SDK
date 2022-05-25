from SCons.Tool import cc,cxx,ar,link
import importlib
assembler = importlib.import_module('SCons.Tool.as')

def generate(env):
    cc.generate(env)
    cxx.generate(env)
    assembler.generate(env)
    ar.generate(env)
    link.generate(env)
    env['CC'] = 'clang'
    env['CXX'] = 'clang++'
    env['AS'] = 'clang'
    env['AR'] = 'llvm-ar'
    env['OBJDUMP'] = 'llvm-objdump'
    env['OBJCOPY'] = 'llvm-objcopy'
    env['NM'] = 'llvm-nm'
    env['READELF'] = 'llvm-readelf'
    env['PROGSUFFIX'] = '.elf'    
    
def exists(env):
    return True