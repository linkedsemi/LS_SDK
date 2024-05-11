EXTERN(boot_ram_start)
HAL_LSSHA_Init  = 0x0100099e ;
HAL_LSSHA_SHA256 = 0x01000c2a ;
HAL_LSSHA_DeInit = 0x010009b0 ;
SECTIONS
{
    .text 0x10001000:
    {
        *(.text.boot_ram_start)
        *(.text* .rodata*)
        __boot_ram_end__ = .;
    }
    .bss (NOLOAD):
    {
        *(.bss* )
    }
}
