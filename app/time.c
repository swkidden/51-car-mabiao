/*
 * @LastEditors: Dark white
 * @LastEditTime: 2022-05-25 20:55:38
 * @FilePath: \mabiao\app\time.c
 * @Description:
 *
 * Copyright (c) 2022 by Dark white, All Rights Reserved.
 */
#include "time.h"
#include "../driver/queue.h"
#include "../driver/uart.h"
uint8 hour = 13;
uint8 branch = 0;
uint8 second = 0;
static bit hour_flag;
bit branch_flag;
bit second_flag;
void update_time() {
  static uint8 *data1;
  if (!hour_flag && !branch_flag && !second_flag &&
    QueryPop(data1)) { //帧头检测模式
 //   Send_byte(*data1);
	//	Send_byte(hour_flag);	
    switch (*data1) {
    case 0x61:
      hour_flag = 1;
      break;
    case 0x62:
      branch_flag = 1;
      break;
    case 0x63:
      second_flag = 1;
      break;
    default:
      break;
    }
  } else if (hour_flag) {
   // Send_string("hour_flag:1 /n"); 
    if (QueryPop(data1)) {
   //   Send_string("set time/n"); 
      hour = *data1;
      hour_flag = 0;
    //  Send_string("hour_flag:0 /n"); 
    }
  } else if (branch_flag) { //数据处理
    if (QueryPop(data1)) {
      Send_byte(*data1);
      branch = *data1;
      branch_flag = 0;
    }
  } else if (second_flag) { //数据处理
    if (QueryPop(data1)) {
      Send_byte(*data1);
      second = *data1;
      second_flag = 0;
    }
  }
 }