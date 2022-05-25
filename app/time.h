/*
 * @LastEditors: Dark white
 * @LastEditTime: 2022-05-25 18:55:59
 * @FilePath: \mabiao\app\time.h
 * @Description: 
 * 
 * Copyright (c) 2022 by Dark white, All Rights Reserved. 
 */
#ifndef _TIME_H_
#define _TIME_H_
#include"../driver/HAL_INIT.h"
extern uint8 hour;
extern uint8 branch;
extern uint8 second;
void update_time();
#endif