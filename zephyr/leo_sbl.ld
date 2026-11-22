#ifdef CONFIG_XIP
KEEP(*(.rodata.__info_array))
. = ALIGN(0x100);
. = 0x2060;
#endif