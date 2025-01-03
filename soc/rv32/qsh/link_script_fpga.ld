MEMORY
{
    ROM (rx) 	: ORIGIN = 0x01000000, LENGTH = 0x8000
    FLASH (rx)	: ORIGIN = 0x08000000, LENGTH = 0x20000
    RAM (wx) 	: ORIGIN = 0x10000000, LENGTH = 0x100000
}
ENTRY(Reset_Handler)
SECTIONS
{
	.text :
	{
		KEEP(*(.text.Reset_Handler))
		*(.text* .*srodata* .*rodata*)
		*(.xip_banned*)
		*(.ABS*)
		. = ALIGN(8);
	} >ROM

    __data_lma__ = ALIGN (4);

	.data :
	{
		. = ALIGN(4);
        __data_start__ = .;
		*(vtable)
		*(.*data*)
		. = ALIGN(4);
        __data_end__ = .;
	} >RAM AT>ROM

	.bss :
	{
		. = ALIGN(4);
		__bss_start__ = .;
		*(.*bss*)
		. = ALIGN(0x4);
		__bss_end__ = .;
		
	} >RAM

	PROVIDE(end = .);

	__StackTop = ORIGIN(RAM) + LENGTH(RAM);
	PROVIDE(__global_pointer$ = ORIGIN(RAM) + 2K);
}
