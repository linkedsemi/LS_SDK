md %2\build\Exe
%1\tools\srec_cat.exe -o %2\build\Exe\info_head.bin -bin -gen 0 12 -repd 0x3c 0x3c 0xa5 0xa5 0xc3 0xc3 0x5a 0x5a 0x80 0x00 0x00 0x00 -gen 12 16 -constle -l %1\soc\arm_cm\lm3050\bin\bram.bin -bin 4 -gen 16 20 -constle 0x20001000 4 -gen 20 24 -constle 0xffffffff 4 -gen 24 26 -constle 0x0000 2 -cbnle 26 2 2
%1\tools\srec_cat.exe -o %2\build\Exe\dummy_array.bin -bin -gen 0 96 -constant 0xff
%1\tools\srec_cat.exe -o %2\build\Exe\info_sbl.bin -bin %2\build\Exe\info_head.bin -bin -crc32le 28 %2\build\Exe\dummy_array.bin -bin -of 32 %1\soc\arm_cm\lm3050\bin\bram.bin -bin -of 128 -crc32le -max-a %1\soc\arm_cm\lm3050\bin\bram.bin -bin -of 128
%1\tools\srec_cat.exe -o %1\soc\arm_cm\lm3050\__info_array.c -c-a __info_array %2\build\Exe\info_sbl.bin -bin