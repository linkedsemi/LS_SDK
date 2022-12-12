EXTERN(boot_ram_start)
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
