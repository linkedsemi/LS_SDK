#include "ls_hal_owm.h"
#include "ls_msp_owm.h"
#include "ls_soc_gpio.h"
#include "platform.h"
#include "log.h"

#include <string.h>
#define DQ  PH00
#define BUF_SIZE 256

static OWM_HandleTypeDef    OWM_Hdl;
#define   SEARCH_ROM                  0xF0     // 搜索ROM指令
#define   DS18B20_SKIP_ROM            0xCC     // 跳过ROM指令
#define   DS18B20_CONVERT_T           0x44     // 温度转换指令
#define   DS18B20_READ_SCRATCHPAD     0xBE     // 读取暂存区指令

uint8_t test_data[BUF_SIZE];
volatile uint8_t _ACK;
enum lsowm_type
{
    LSOWM_WRITE_DATA,
    LSOWM_READ_DATA,
};
volatile enum lsowm_type lsowm_type_flag;

void OWM_Init_Func(void)
{
    OWM_Hdl.Instance = LSOWM;
    OWM_Hdl.per_div = 0x10;  // 最小0x10
    OWM_Hdl.dat_len = 0x7;
    OWM_Hdl.flt_num = 0x1;
    HAL_OWM_Init(&OWM_Hdl); 
}

void HAL_LSOWM_RstComplete_Callback(OWM_HandleTypeDef* owm, uint8_t ack)
{
    _ACK =  ack;
}

void HAL_LSOWM_TxComplete_Callback(OWM_HandleTypeDef* owm)
{
    lsowm_type_flag = LSOWM_READ_DATA;
}

void HAL_LSOWM_RxComplete_Callback(OWM_HandleTypeDef* owm)
{
    uint32_t temp = test_data[0]|test_data[1]<<8;
    LOG_I("%d",temp);
}

void Start18B20(OWM_HandleTypeDef *owm)
{
    _ACK = 1;
    uint8_t temp[2] = {DS18B20_SKIP_ROM,DS18B20_CONVERT_T};
    HAL_OneWireRst_IT(owm);
    while (_ACK);
    lsowm_type_flag = LSOWM_WRITE_DATA;
    HAL_OWM_WriteData_IT(owm,temp,2);
    while (lsowm_type_flag == LSOWM_WRITE_DATA);
}

void read18B20(OWM_HandleTypeDef *owm)
{
    uint8_t temp[2] = {DS18B20_SKIP_ROM,DS18B20_READ_SCRATCHPAD};
    _ACK = 1;
    HAL_OneWireRst_IT(owm);
    while (_ACK);
    lsowm_type_flag = LSOWM_WRITE_DATA;
    HAL_OWM_WriteData_IT(owm,temp,2);
    while (lsowm_type_flag == LSOWM_WRITE_DATA);
    HAL_OWM_ReadData_IT(owm,test_data,2);
    while (lsowm_type_flag == LSOWM_READ_DATA);

}

int main()
{   
    sys_init_none();
    pinmux_owm_init(DQ);
    OWM_Init_Func();
    Start18B20(&OWM_Hdl);
    read18B20(&OWM_Hdl);
    while (1)
    {

    }
}