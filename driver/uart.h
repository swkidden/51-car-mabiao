/*
 * @LastEditors: Dark white
 * @LastEditTime: 2022-05-25 00:25:02
 * @FilePath: \mabiao\driver\uart.h
 * @Description: uart driver 以至过往作业
 * 
 * Copyright (c) 2022 by Dark white, All Rights Reserved. 
 */
#ifndef _UART_H_
#define _UART_H_
#include "HAL_INIT.h"
void uart_init(uint8 method,uint8 double_rate);
void Send_byte(unsigned char byte);
void Send_string(uint8 *table);
#endif