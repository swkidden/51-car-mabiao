/*
 * @LastEditors: Dark white
 * @LastEditTime: 2022-05-24 16:38:59
 * @FilePath: \mabiao\app\key_task.h
 * @Description:按键处理响应包含部分eeprom操作
 * 
 * Copyright (c) 2022 by Dark white, All Rights Reserved. 
 */
#ifndef _KEY_TASK_H
#define _KEY_TASK_H
#include"../driver/key.H"
void write_memory();
void read_memory();
void key_regesiter();
#endif