#ifndef QSPIV2_CONFIG_H_
#define QSPIV2_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif
#ifdef FPGA_TEST
#define QSPI_CLK_CYCLE 3
#else
#define QSPI_CLK_CYCLE 1
#endif
#define QSPI_CS_INTERVAL 4
#define QSPI_CS_HOLD 2
#define QSPI_CS_SETUP 2

//(neg,delay) = (0,0), (1,1),(0,1), (1,2),(0,2), (1,3),(0,3)
#ifdef BOOT_ROM
#define QSPI_CAPTURE_DELAY 0
#define QSPI_CAPTURE_NEG 0
#else
//fail
// #define QSPI_CAPTURE_NEG 0
// #define QSPI_CAPTURE_DELAY 3
//fail
// #define QSPI_CAPTURE_NEG 1
// #define QSPI_CAPTURE_DELAY 3
//ok
// #define QSPI_CAPTURE_NEG 0
// #define QSPI_CAPTURE_DELAY 2
//ok
#define QSPI_CAPTURE_NEG 1
#define QSPI_CAPTURE_DELAY 2
//ok
// #define QSPI_CAPTURE_NEG 0
// #define QSPI_CAPTURE_DELAY 1
//ok
// #define QSPI_CAPTURE_NEG 1
// #define QSPI_CAPTURE_DELAY 1
#endif

#ifdef __cplusplus
}
#endif

#endif

