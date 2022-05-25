/*
 * @LastEditors: Dark white
 * @LastEditTime: 2022-05-25 12:21:48
 * @FilePath: \mabiao\driver\queue.h
 * @Description: 
 * 
 * Copyright (c) 2022 by Dark white, All Rights Reserved. 
 */
#ifndef __QUEUE_H_
#define __QUEUE_H_
#include "HAL_INIT.h"
#define QUEUE_SIZE 32        //需要定义的空间大小为帧大小*帧数，例如帧大小为8Byte共4帧则为32
uint8 QueryPush(uint8 dat);
uint8 QueryPop(uint8* dat);
#endif