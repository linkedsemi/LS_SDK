#ifndef __CSKY_FLASH_OS_H__

#define __CSKY_FLASH_OS_H__

#define INDEVSECTION __attribute__((section ("DevDscr")))
#define ININITSECTION __attribute__((section ("DevInit")))
#define INHRSTSECTION __attribute__((section ("DevHReset")))


#define FLASH_DRV_VERS 5
#define SECTOR_NUM 128

struct Device {
  unsigned long Start;
  unsigned long Length;
  unsigned long PageSize;
};

struct FlashDevice {
  unsigned int Ver; // Driver Version
  char DevName[128]; // Device Name
  char CPU[32]; // must in low case
  int FlashID; // the Flash ID
  char FlashType[128]; // 
  unsigned int TotalSize; // the Flash type which is Reserved value
  int IsAccDirect; // 0 is not access directly else yes
  int rangeNumbers;
  struct Device Devs[SECTOR_NUM];
  char VendorName[128]; // Vendor Name
};

#endif // __CSKY_FLASH_OS_H__