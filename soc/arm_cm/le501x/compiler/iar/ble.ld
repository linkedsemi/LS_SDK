define memory mem with size = 4G;

define region RAM = mem: [from 0x0 to 0xc000];
define region FLASH = mem: [from 0x18034000 to 0x18080000];
define symbol __data_start__ = 0x750;

include "common.ld";