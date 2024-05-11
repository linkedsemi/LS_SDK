#include "ls_hal_owm.h"
#include "ls_msp_owm.h"
#include "ls_soc_gpio.h"
#include "platform.h"
#include "log.h"

#include <string.h>
#define DQ  PH00
static OWM_HandleTypeDef    OWM_Hdl;
#define BUF_SIZE 256

#define   SEARCH_ROM                  0xF0     // 搜索ROM指令
#define   MATCH_ROM                   0x55     // 匹配ROM指令
#define   DS18B20_SKIP_ROM            0xCC     // 跳过ROM指令
#define   DS18B20_CONVERT_T           0x44     // 温度转换指令
#define   DS18B20_READ_SCRATCHPAD     0xBE     // 读取暂存区指令

uint8_t test_data[BUF_SIZE];
void Error_Handler(void)
{
    while(1);
}

void OWM_Init_Func(void)
{
    OWM_Hdl.Instance = LSOWM;
    OWM_Hdl.per_div = 0x10;
    OWM_Hdl.dat_len = 0xf;
    OWM_Hdl.flt_num = 0x1;
    HAL_OWM_Init(&OWM_Hdl);
}

void Start18B20(OWM_HandleTypeDef *owm)
{
    uint8_t temp[2] = {DS18B20_SKIP_ROM,DS18B20_CONVERT_T};
    if(!HAL_OneWireRst(owm))
    {
        HAL_OWM_WriteData(owm,temp,2);
    }
}

/*DS18B20读取温度*/
HAL_StatusTypeDef read18B20(OWM_HandleTypeDef *owm)
{
    uint8_t temp[2] = {DS18B20_SKIP_ROM,DS18B20_READ_SCRATCHPAD};
    volatile uint8_t TLSB, TMSB, th, T;
    if(!HAL_OneWireRst(owm))
    {
        // ROM指令
        HAL_OWM_WriteData(owm,temp,2);
        HAL_OWM_ReadData(owm,test_data,2);
        TLSB = test_data[0];
        TMSB = test_data[1];
        th = (TMSB << 4) + (TLSB >> 4);
        T = th;
        if (TMSB > 0x08)   // 对负温度的处理
        {
            th = ~th + 1; // 取反加1
            T = -th;   // 负数
        }
        return T;
    }
    else
        return HAL_ERROR;
}

int main()
{
    uint8_t temp;    
    sys_init_none();
    pinmux_owm_init(DQ);
    OWM_Init_Func();
    while (1)
    {
        Start18B20(&OWM_Hdl);
        temp = read18B20(&OWM_Hdl);
        if(temp == HAL_ERROR)
        {
            LOG_I("No device answer");
        }
        else
        {
            LOG_I("temp=%d",temp);
        }
    }  
}