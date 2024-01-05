#include "sdk_config.h"

#if (UART_TEST)
#include <string.h>
#include <ctype.h>
#include "platform.h"
#include "ls_sig_mesh.h"
#include "log.h"
#include "ls_hal_uart.h"
#include "ls_soc_gpio.h"

extern SIGMESH_NodeInfo_TypeDef Node_Get_Proved_State;
extern SIGMESH_NodeInfo_TypeDef Node_Proved_State;

#define  AT_RECV_MAX_LEN 32
enum UART_TXCB_EVENT
{
    UART_TXCB_EVENT_IDLE=0,
    UART_TXCB_EVENT_SIGMESH_UBD,
    UART_TXCB_EVENT_SIGMESH_RST,
};    
enum UART_TXCB_EVENT txcall_event=UART_TXCB_EVENT_IDLE;
uint8_t at_recv_char;
uint8_t at_recv_buffer[AT_RECV_MAX_LEN];
uint8_t at_recv_index = 0;
uint8_t at_recv_count = 0;
static bool uart_tx_busy = false; 
UART_HandleTypeDef UART_Config;


typedef struct _at_recv_data
{
    uint16_t param_len;
    uint8_t param[AT_RECV_MAX_LEN];
} at_recv_t;

at_recv_t at_cmd_event;

static void uart_write(uint8_t *value,uint16_t length);

int htoi(char s[])  
{  
    int i;  
    int n = 0;  
    if (s[0] == '0' && (s[1]=='x' || s[1]=='X'))  
    {  
        i = 2;  
    }  
    else  
    {  
        i = 0;  
    }  
    for (; (s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'z') || (s[i] >='A' && s[i] <= 'Z');++i)  
    {  
        if (tolower(s[i]) > '9')  
        {  
            n = 16 * n + (10 + tolower(s[i]) - 'a');  
        }  
        else  
        {  
            n = 16 * n + (tolower(s[i]) - '0');  
        }  
    }  
    return n;  
} 


static void at_send_rsp(char *str)
{
     uart_write((uint8_t *)str, strlen(str));
}

static void at_recv_cmd_reset(uint8_t *cmd, uint8_t cmd_len)
{
          txcall_event=UART_TXCB_EVENT_IDLE;
        if ((*(cmd) == 'e') && (*(cmd+1) == 't'))
        {
            if ((Node_Get_Proved_State == PROVISIONED_OK) || (Node_Proved_State == MESH_PROV_SUCCEED))
            {
                at_send_rsp("OK\r\n");
                txcall_event=UART_TXCB_EVENT_SIGMESH_UBD;
            }
            else
            {
                at_send_rsp("unprov fail\r\n"); 
            }    
        }
        else
        {
            at_send_rsp("cmd_Err\r\n");
        }
}

static void at_recv_cmd_reboot(uint8_t *cmd, uint8_t cmd_len)
{
        txcall_event=UART_TXCB_EVENT_IDLE;
        if ((*(cmd) == 'o') && (*(cmd+1) == 'o') && (*(cmd+2) == 't'))
        {
            at_send_rsp("OK\r\n");
            txcall_event=UART_TXCB_EVENT_SIGMESH_RST;
        }
        else
        {
            at_send_rsp("cmd_Err\r\n");
        }
}

static void at_cmd_recv_handler(void *arg)
{
    at_recv_t *param =(at_recv_t *) arg;
    switch(param->param[0])
    {
        case 'b':
            at_recv_cmd_reboot(&(param->param[1]),param->param_len - 2);
        break;
        case 's':
            at_recv_cmd_reset(&(param->param[1]),param->param_len - 2);
        break;

        default: break;
    }   
}

static void at_recv(uint8_t c)
{
    switch(at_recv_count)
    {
        case 0:
            if(c == 'r')
                at_recv_count++;
            else
                at_recv_count = 0;
            break;
        case 1:
            if(c == 'e')
                at_recv_count++;
            else
                at_recv_count = 0;
            break;
        case 2:
            at_recv_buffer[at_recv_index++] = c;
            if((c == '\n')
               ||(at_recv_index >= AT_RECV_MAX_LEN))
            {
                // LOG_I("recv_index %d",at_recv_index);
                memcpy(at_cmd_event.param,at_recv_buffer,at_recv_index);
                at_cmd_event.param_len = at_recv_index;
                at_cmd_recv_handler((void *)&at_cmd_event);
                at_recv_count = 0;
                at_recv_index = 0;
            }
            break;
        default: 
            
            break;
    }
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    uart_tx_busy = false;
      if(txcall_event==UART_TXCB_EVENT_SIGMESH_UBD)
        {
       //ls_sig_mesh_disable();
          Node_Get_Proved_State = UNPROVISIONING;
          Node_Proved_State = MESH_PROV_STARTED;
        }
        else if (txcall_event==UART_TXCB_EVENT_SIGMESH_RST)
        {
        platform_reset(0);
              while(1);
        }
        
        txcall_event = UART_TXCB_EVENT_IDLE;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    at_recv(at_recv_char);
    HAL_UART_Receive_IT(&UART_Config, &at_recv_char, 1);
}

static void uart_write(uint8_t *value,uint16_t length)
{
    if(uart_tx_busy)
    {
        LOG_I("Uart tx busy, data discard!");
    }
    else
    {
        uart_tx_busy = true;
        HAL_UART_Transmit_IT(&UART_Config, value, length);
        // for(uint8_t i=0;i<length;i++)
        // {
        //     LOG_I("%c",*(value+i));
        // }
    }   
}

void ls_uart_init(void)
{
    pinmux_uart3_init(PB00, PB01);
    io_pull_write(PB01, IO_PULL_UP);
    UART_Config.UARTX = UART3;
    UART_Config.Init.BaudRate = UART_BAUDRATE_921600;
    UART_Config.Init.MSBEN = 0;
    UART_Config.Init.Parity = UART_NOPARITY;
    UART_Config.Init.StopBits = UART_STOPBITS1;
    UART_Config.Init.WordLength = UART_BYTESIZE8;
    HAL_UART_Init(&UART_Config);
    HAL_UART_Receive_IT(&UART_Config, &at_recv_char, 1); 
}

#endif //(UART_TEST)
