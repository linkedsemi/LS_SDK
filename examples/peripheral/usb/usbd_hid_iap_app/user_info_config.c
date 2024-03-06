/*
#if ( USER_APP_TYPE == 0 )
#if defined(__ICCARM__)
#pragma location = 0x18007200
__root const char __user_info_config[256] = {0X11,0x22,0x33,0x44,0xff,0xff,0xff,0xff};
#elif defined(__CC_ARM)
const char __user_info_config[256] __attribute__((at(0x18007200))) = {0X11,0x22,0x33,0x44,0xff,0xff,0xff,0xff};
#elif defined(__GNUC__)
const char __user_info_config[256] __attribute__((section(".ARM.__at_0x18007200"))) = {0X11,0x22,0x33,0x44,0xff,0xff,0xff,0xff};
#endif
#elif ( USER_APP_TYPE == 1 )

#elif ( USER_APP_TYPE == 2 )
#endif
*/


const unsigned char __user_info_config[256] = {
0X44,0x33,0x22,0x11,
0xff,0xff,0xff,0xff
};

