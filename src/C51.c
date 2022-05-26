/*
 * @LastEditors: Dark white
 * @LastEditTime: 2022-05-26 00:18:09
 * @FilePath: \51-car-mabiao\src\C51.c
 * @Description:
 *
 * Copyright (c) 2022 by Dark white, All Rights Reserved.
 */
#include "../app/display.h"
#include "../app/key_task.h"
#include "../app/wendu.h"
#include "../app/time.h"
#include "../driver/HAL_INIT.h"
#include "../driver/uart.h"
/* ------------STATIC---------------------- */
static uint16 count;
static uint8 ms = 0;
static uint8 s = 0;
static uint8 ten_s = 0;
/*----------- global variable----------------*/
uint8 page;
uint8 speed_h;  //报警值km/h
uint8 speed_km; // km/s
uint8 diameter;
uint8 mileage;
uint16 speed_m;      // m/s
uint16 mileage_temp; //每1公里清零一次用于累加mileage
uint16 n = 0;        //转速r/min

/* ------------HARDWARE---------------------- */
sbit beep = P3 ^ 2;
bit beep1 = 1;
/* ------------FUNCTION---------------------- */
static void alarm();

void main() {
  LCD1602_cls(); //Initialize LCD
  uart_init(1, 1);
  hal_init();
  read_memory(); //eeprom
  while (1) {
    alarm();
    key_regesiter();
    display(page);
    update_time();
    /* 1s call */
    if (ten_s >= 20) {
      ten_s = 0;
      Get_Tmp();
    }
  }
}

void time0() interrupt 1 //timer 0
{
  TH0 = 0x3C;
  TL0 = 0xb0;      // 50ms timing
  ms++;            // 50ms
  ten_s++;         //For timing 10s
  if (page == 6) { //Save success page
    s++;
  }
  /* 蜂鸣器 */
  if (beep1) {
    beep = ~beep;
  } else {
    beep = 1;
  }

  /*---------------- Calculation speed--------------- */
  if (ms >= 20) { // 1s定时
    ms = 0;
    EX1 = 0; //关闭外部中断，保证变量在计算的时候不会增加
    n = count * 60; // 60s/1s
    count = 0; //清零变量
    EX1 = 1;   //打开外部中断
    speed_m = n * diameter * 2.54 * 3.14 / 100 / 60; //轮径单位英寸 1英寸=2.54cm m/min
    speed_km = speed_m * 3.6;
    mileage_temp += speed_m;
    if (mileage_temp >= 1000) {
      mileage_temp = 0;
      mileage++;
    }
    if (mileage >= 99) {
      mileage = 0;
    }
  }
  /* ----------page6 successful page for 1.5s --------*/
  if (s % 30 == 0 && page == 6) { // 1.5s
    s = 0;
    page = 0;
  }
}

void int1() interrupt 2 { //External interrupt 1
  count++;                //用于计算圈数
}

static void alarm() {
  if ((speed_km > speed_h)) {
    beep1 = 1;
  } else {
    beep1 = 0;
  }
}