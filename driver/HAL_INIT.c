/*
 * @LastEditors: Dark white
 * @LastEditTime: 2022-05-25 17:21:10
 * @FilePath: \mabiao\driver\HAL_INIT.c
 * @Description: 
 * 
 * Copyright (c) 2022 by Dark white, All Rights Reserved. 
 */
#include "HAL_INIT.h"
void hal_init(){
/*---Timer 0------*/
	TMOD &= 0xF0;		//�����ʱ��0ģʽλ
	TMOD |= 0x01;
   TH0 = 0x3C;
	 TL0 = 0xb0; 
   ET0=1;
   TR0=1;
/*---External interrupt 1------*/ 
   EX1=1;
   IT1=1;
   EA=1;
}