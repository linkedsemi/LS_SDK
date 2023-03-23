#ifndef _DISK_PORT_H
#define _DISK_PORT_H

#include "ff.h"
#include "diskio.h"

DSTATUS RAM_disk_status(void);
DSTATUS RAM_disk_initialize(void);
DRESULT RAM_disk_read(BYTE *buff, DWORD sector, UINT count);
DRESULT RAM_disk_write(const BYTE *buff, DWORD sector, UINT count);
DRESULT RAM_disk_ioctl(BYTE cmd, void *buff);

#endif
