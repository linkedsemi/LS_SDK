MEMORY
{
    FLASH (rx)	: ORIGIN = 0x08000000, LENGTH = 0x100000
    RAM1 (wx) 	: ORIGIN = 0x10000000, LENGTH = 0x80000
    RAM2 (wx) 	: ORIGIN = 0x10080000, LENGTH = 0xC0000
}

SECTIONS
{
	.text :
	{
		KEEP(*(.text.Reset_Handler))
		*(.text* .*srodata* .*rodata*)
		*(.xip_banned*)
		*(.ABS*)
		. = ALIGN(8);
	} >FLASH

    __data_lma__ = ALIGN (4);

	.data :
	{
		. = ALIGN(4);
        __data_start__ = .;
		*(vtable)
		*(.*data*)
		. = ALIGN(4);
        __data_end__ = .;
	} >RAM1 AT>FLASH

	.bss :
	{
		. = ALIGN(4);
		__bss_start__ = .;
		*(.*bss*)
		. = ALIGN(0x4);
		__bss_end__ = .;
		
	} >RAM1

	PROVIDE(end = .);

	__StackTop = ORIGIN(RAM1) + LENGTH(RAM1);
	PROVIDE(__global_pointer$ = ORIGIN(RAM1) + 2K);
}
