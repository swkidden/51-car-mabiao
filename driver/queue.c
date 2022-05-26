/*
 * @LastEditors: Dark white
 * @LastEditTime: 2022-05-25 23:49:05
 * @FilePath: \51-car-mabiao\driver\queue.c
 * @Description: 先入先出队列用于串口
 *
 * Copyright (c) 2022 by Dark white, All Rights Reserved.
 */
#include"queue.h"
#include "HAL_INIT.h"
static unsigned char receive_buff[QUEUE_SIZE] = {0};
unsigned char front = 0;
unsigned char rear = 0;

unsigned char QueryPush(unsigned char dat) {
  if (((front + 1) % QUEUE_SIZE) != rear) //队列没满
  {
    receive_buff[front++] = dat;
    front %= QUEUE_SIZE;
    return 1;
  } else
    return 0;
}

unsigned char QueryPop(unsigned char *dat) {
  if (front != rear) //队列不为空
  {
    *dat = receive_buff[rear++];
    rear %= QUEUE_SIZE;
    return 1;
  }
  return 0;
}
