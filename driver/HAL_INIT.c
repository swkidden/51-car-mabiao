/*
 * @LastEditors: Dark white
 * @LastEditTime: 2022-05-26 00:19:58
 * @FilePath: \51-car-mabiao\driver\HAL_INIT.c
 * @Description: 
 * 
 * Copyright (c) 2022 by Dark white, All Rights Reserved. 
 */
#include "HAL_INIT.h"
void hal_init(){
/*---Timer 0------*/
   EXEN2=0;
	TMOD &= 0xF0;		//清除定时器0模式位
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