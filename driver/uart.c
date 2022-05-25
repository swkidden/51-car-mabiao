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

	TMOD &= 0x0F;		//�����ʱ��1ģʽλ
	TMOD |= 0x20;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ
  TH1 = 204;
  TL1 = 204;
	ET1 = 0;		//��ֹ��ʱ��1�ж�
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

void uart(void) interrupt 4 { //���ڽ���
  if (RI) {
    QueryPush(SBUF); // ��������
    RI = 0;         // ��������жϱ�־λ
  }
}