from SCons.Tool import cc,cxx,ar,link
import importlib
assembler = importlib.import_module('SCons.Tool.as')

def generate(env):

    cc.generate(env)
    cxx.generate(env)
    assembler.generate(env)
    ar.generate(env)
    link.generate(env)
    env['CC'] = 'arm-none-eabi-gcc'
    env['CXX'] = 'arm-none-eabi-g++'
    env['AS'] = 'arm-none-eabi-gcc'
    env['AR'] = 'arm-none-eabi-gcc-ar'
    env['OBJDUMP'] = 'arm-none-eabi-objdump'
    env['OBJCOPY'] = 'arm-none-eabi-objcopy'
    env['NM'] = 'arm-none-eabi-nm'
    env['READELF'] = 'arm-none-eabi-readelf'
    env['PROGSUFFIX'] = '.elf'    
    
def exists(env):
    return True