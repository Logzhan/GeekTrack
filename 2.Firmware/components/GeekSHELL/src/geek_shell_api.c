#include "driver/uart.h"
#include "geek_shell_api.h"

// 配置UART0作为串口命令行输入输出口
static int SHELL_UART = UART_NUM_0;

// 串口命令行相关
Shell shell;
char shellBuffer[512];

/**
 * @brief 用户shell写
 * 
 * @param data 数据
 */
signed short userShellWrite(char* data, unsigned short len)
{
    uart_write_bytes(SHELL_UART, (const char *)data, len);
    return len;
}
/**
 * @brief 用户shell读
 * 
 * @param data 数据
 * @return char 状态
 */
signed short userShellRead(char *data, unsigned short len){
    return (uart_read_bytes(SHELL_UART, (uint8_t *)data, len, portMAX_DELAY) == 1)
        ? 1 : -1;
}

/**
 * @brief 用户shell初始化
 * 
 */
void userShellInit(int shellUart)
{
    SHELL_UART = shellUart;

    uart_config_t uartConfig = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    uart_param_config(SHELL_UART, &uartConfig);
    uart_driver_install(SHELL_UART, 256 * 2, 0, 0, NULL, 0);
    //uart_flush_input(0);
    shell.write = userShellWrite;
    shell.read  = userShellRead;
    shellInit(&shell, shellBuffer, 512);
}

/**
 * @brief 获取shell对象
 * 
 */
Shell* GetEsp32Shell(void)
{
    return (&shell);
}

/**
 * @brief ESP32插入尾行前
 * 
 */
void esp32WriteShellEndLine(char* line){
    shellWriteEndLine(&shell, line);
}