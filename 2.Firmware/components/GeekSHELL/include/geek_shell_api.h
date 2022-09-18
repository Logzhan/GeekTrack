/**
 * @file      geek_shell_api.h
 * @author    log_zhan (719901725@qq.com)
 * @brief     shell esp32 config interface
 * @version   3.0.0
 * @date      2021-07-24
 * @copyright (c) 2021 log_zhan
*/

#ifndef __GEEK_SHELL_API_H__
#define __GEEK_SHELL_API_H__

#include "geek_shell.h"

void userShellInit(int shellUart);
Shell* GetEsp32Shell(void);
void esp32WriteShellEndLine(char* line);

#endif
