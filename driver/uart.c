/*
 * @LastEditors: Dark white
 * @LastEditTime: 2022-05-25 19:19:05
 * @FilePath: \mabiao\driver\uart.c
 * @Description:
 *
 * Copyright (c) 2022 by Dark white, All Rights Reserved.
 */
#include "queue.h"
#include "uart.h"
void uart_init (unsigned char method, unsigned char double_rate) {

  if (double_rate) {
    PCON = PCON | (1 << 7);
  } else {
    PCON = PCON & 0x7f;
  }

  switch (method) {
  case 1:
    SCON = 0X50;
    break;
  case 2:
    SCON = 0X90;
    EA = 1;
    ES = 1;
    return;
  }

	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式
  TH1 = 204;
  TL1 = 204;
	ET1 = 0;		//禁止定时器1中断
  EA = 1;
  TR1 = 1;
  ES = 1;
}

void Send_byte(unsigned char byte) {
  SBUF = byte;
  while (TI == 0);
  TI = 0;
}

void Send_string(unsigned char *table) {

  while (*table) {
    Send_byte(*table++);
  }
}

void uart(void) interrupt 4 { //串口接收
  if (RI) {
    QueryPush(SBUF); // 接收数据
    RI = 0;         // 清除接收中断标志位
  }
}