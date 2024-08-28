MEMORY
{
    RAM (wx) : ORIGIN = 0x10000000, LENGTH = 0x10000
}
ENTRY(Reset_Handler)
SECTIONS
{
	.text :
	{
		KEEP(*(.text.Reset_Handler))
		*(.text* .*rodata*)
		*(.xip_banned*)
		*(.ABS*)
		. = ALIGN(8);
	} >RAM

    __data_lma__ = ALIGN (4);

	.data :
	{
		. = ALIGN(4);
        __data_start__ = .;
		*(vtable)
		*(.*data*)
		. = ALIGN(4);
        __data_end__ = .;
	} >RAM 

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
