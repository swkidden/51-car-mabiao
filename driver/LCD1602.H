/*
 * @LastEditors: Dark white
 * @LastEditTime: 2022-05-25 00:23:15
 * @FilePath: \mabiao\driver\LCD1602.H
 * @Description: 
 * 
 * Copyright (c) 2022 by Dark white, All Rights Reserved. 
 */
#ifndef _LCD1602_H_
#define _LCD1602_H_
#include "HAL_INIT.h"
#define uchar unsigned char 
#define uint unsigned int
#define LCD1602_dat P0	//数据并行口宏定义
void LCD1602_delay(uint T);	
void LCD1602_write(uchar order,dat)	;
void LCD1602_writebyte(uchar *prointer)	;
void LCD1602_cls();	
#endif