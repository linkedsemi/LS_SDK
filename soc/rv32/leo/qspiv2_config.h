#ifndef QSPIV2_CONFIG_H_
#define QSPIV2_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#define QSPI_CLK_CYCLE 1
#define QSPI_CS_INTERVAL 4
#define QSPI_CS_HOLD 2
#define QSPI_CS_SETUP 2

//(neg,delay) = (0,0),(1,1),(0,1),(1,2)
#define QSPI_CAPTURE_DELAY 1 
#define QSPI_CAPTURE_NEG 0

#ifdef __cplusplus
}
#endif

#endif
