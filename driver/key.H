/*
 * @LastEditors: Dark white
 * @LastEditTime: 2022-05-26 11:51:36
 * @FilePath: \51-car-mabiao\driver\key.H
 * @Description:
 *
 * Copyright (c) 2022 by Dark white, All Rights Reserved.
 */
#ifndef __KEY_H_
#define __KEY_H_

#include "HAL_INIT.h"
/**********************************
            PIN口定义
**********************************/
sbit KEY_LEFT = P1 ^ 1;
sbit KEY_DOWN = P1 ^ 2;
sbit KEY_UP = P1 ^ 3;
sbit KEY_RIGHT = P1 ^ 4;
/**********************************
            FUNCTIOn定义
**********************************/
uint8 Key_scan(); //独立按键检测
/**********************************
            宏定义
**********************************/
#define flag_left 1
#define flag_right 4
#define flag_down 2
#define flag_up 3
#endif
