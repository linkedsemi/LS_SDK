EXTERN(boot_ram_start)
HAL_LSSHA_Init  = 0x00001dc8 ;
HAL_LSSHA_SHA256 = 0x00001de4 ;
HAL_LSSHA_DeInit = 0x00001dd6 ;
SECTIONS
{
    .text 0x20001000:
    {
        *(.text.boot_ram_start)
        *(.text*)
        __boot_ram_end__ = .;
    }
    .bss (NOLOAD):
    {
        *(.bss* )
    }
}
