
initialize by copy with packing = none {section .intvec,section __iar_init$$done.xip_banned*,rw};
place at start of RAM {section .intvec};
place at address mem:__data_start__ {rw};
place at start of FLASH {section .intvec_init};
place in FLASH {ro};

define block HEAP with alignment = 4,size = 0x200 {};
define block RESET_RETAIN with alignment = 4,size = 8 {};
define block CSTACK with alignment = 4,size = 0x1000 {};
place in RAM {block HEAP,block RESET_RETAIN, block CSTACK};
"dmacs": place noload at end of RAM {section DMARAM, section DMAC1};