MEMORY
{
    SHARE (wx)      : ORIGIN = 0x10138000 - 8K, LENGTH = 8K
    RAM (wx)        : ORIGIN = 0x10138000 - 48K - 24K - LENGTH(SHARE), LENGTH = 48K + 24K
    NEXT_RAM        : ORIGIN = 0x10000000, LENGTH = 0x10138000 - 0x10000000 - LENGTH(RAM) - LENGTH(SHARE)
}
ENTRY(Reset_Handler)
SECTIONS
{
	.text :
	{
        __boot_ram_text_start__ = .;
		KEEP(*(.text.Reset_Handler))
		*(.text* .srodata* .rodata*)
		. = ALIGN(8);
        __boot_ram_text_end__ = .;
	} >RAM

    __boot_ram_data_lma__ = ALIGN (4);

	.data :
	{
		. = ALIGN(4);
        __boot_ram_data_start__ = .;
		*(vtable)
		*(.data* .sdata*)
		. = ALIGN(4);
        __boot_ram_data_end__ = .;
	} >RAM

	.bss :
	{
		. = ALIGN(4);
		__boot_ram_bss_start__ = .;
		*(.*bss*)
		. = ALIGN(0x4);
		__boot_ram_bss_end__ = .;
		
	} >RAM

	PROVIDE(end = .);

	/* __total_ram = ORIGIN(RAM) + LENGTH(RAM) + LENGTH(SHARE); */
	__next_ram_size = LENGTH(NEXT_RAM);
	PROVIDE(__global_pointer$ = ORIGIN(RAM) + 2K);
}
