from SCons.Tool import cc,ar,link
import importlib
assembler = importlib.import_module('SCons.Tool.as')

def generate(env):
    cc.generate(env)
    assembler.generate(env)
    ar.generate(env)
    link.generate(env)
    env['CC'] = 'riscv64-unknown-elf-gcc'
    env['AS'] = 'riscv64-unknown-elf-gcc'
    env['AR'] = 'riscv64-unknown-elf-gcc-ar'
    env['OBJDUMP'] = 'riscv64-unknown-elf-objdump'
    env['OBJCOPY'] = 'riscv64-unknown-elf-objcopy'
    env['NM'] = 'riscv64-unknown-elf-nm'
    env['READELF'] = 'riscv64-unknown-elf-readelf'
    env['PROGSUFFIX'] = '.elf'    
    
def exists(env):
    return True