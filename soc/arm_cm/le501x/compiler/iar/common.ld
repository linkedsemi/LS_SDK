

initialize by copy with packing = none {section .intvec,readwrite,section .xip_banned*};
place at start of RAM {section .intvec};
place at start of FLASH {section .intvec_init};
place in FLASH {readonly,ro section .xip_banned*};
place at address mem:__data_start__ {readwrite,section .xip_banned*};

define block HEAP with alignment = 4,size = 0x200 {};
define block RESET_RETAIN with alignment = 4,size = 8 {};
define block CSTACK with alignment = 4,size = 0x1000 {};
place in RAM {block HEAP,block RESET_RETAIN, block CSTACK};
"dmacs": place noload at end of RAM {section DMARAM, section DMACS};