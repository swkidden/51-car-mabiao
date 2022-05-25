/*
 * @LastEditors: Dark white
 * @LastEditTime: 2022-05-24 16:56:15
 * @FilePath: \mabiao\app\display.c
 * @Description:
 *
 * Copyright (c) 2022 by Dark white, All Rights Reserved.
 */
#include "display.h"
#include "../driver/LCD1602.h"
#include "../src/c51.h"
#include "time.h"
#include "wendu.h"
void display(unsigned char page) {
  if (page == 0) {
    LCD1602_write(0, 0x80);
    /* m/s */
    LCD1602_write(1, 0x30 + speed_m / 100 % 10);
    LCD1602_write(1, 0x30 + speed_m / 10 % 10);
    LCD1602_write(1, 0x30 + speed_m % 10);
    LCD1602_writebyte("m/s ");

    /*mileage*/
    LCD1602_write(1, 0x30 + mileage / 10 % 10);
    LCD1602_write(1, 0x30 + mileage % 10);
    LCD1602_writebyte("km ");

    /* temperature */
    LCD1602_writebyte("c:");
    LCD1602_write(1, 0x30 + temperature / 10 % 10);
    LCD1602_write(1, 0x30 + temperature % 10);

    /* -------------------Second line------------------ */
    LCD1602_write(0, 0xc0);
    /* time */
    LCD1602_writebyte("time: ");
    LCD1602_write(1, 0x30 + hour / 10 % 10);
    LCD1602_write(1, 0x30 + hour % 10);
    LCD1602_writebyte(":");
    LCD1602_write(1, 0x30 + branch / 10 % 10);
    LCD1602_write(1, 0x30 + branch % 10);
    LCD1602_writebyte(":");
    LCD1602_write(1, 0x30 + second / 10 % 10);
    LCD1602_write(1, 0x30 + second % 10);

  } else if (page == 1) {
    LCD1602_write(0, 0x80);
    /* m/s */
    LCD1602_write(1, 0x30 + speed_km / 10 % 10);
    LCD1602_write(1, 0x30 + speed_km % 10);
    LCD1602_writebyte("km/h ");

    /*mileage*/
    LCD1602_write(1, 0x30 + mileage / 10 % 10);
    LCD1602_write(1, 0x30 + mileage % 10);
    LCD1602_writebyte("km ");

    /* temperature */
    LCD1602_writebyte("c:");
    LCD1602_write(1, 0x30 + temperature / 10 % 10);
    LCD1602_write(1, 0x30 + temperature % 10);

    /* -------------------Second line------------------ */
    LCD1602_write(0, 0xc0);
    /* time */
    LCD1602_writebyte("time: ");
    LCD1602_write(1, 0x30 + hour / 10 % 10);
    LCD1602_write(1, 0x30 + hour % 10);
    LCD1602_writebyte(":");
    LCD1602_write(1, 0x30 + branch / 10 % 10);
    LCD1602_write(1, 0x30 + branch % 10);
    LCD1602_writebyte(":");
    LCD1602_write(1, 0x30 + second / 10 % 10);
    LCD1602_write(1, 0x30 + second % 10);

  } else if (page == 2) {
    /* r/min */
    LCD1602_write(0, 0x80);
    LCD1602_write(1, 0x30 + n / 1000 % 10);
    LCD1602_write(1, 0x30 + n / 100 % 10);
    LCD1602_write(1, 0x30 + n / 10 % 10);
    LCD1602_write(1, 0x30 + n % 10);
    LCD1602_writebyte("r/min ");

  } else if (page == 3) {
    LCD1602_write(0, 0x80);
    LCD1602_writebyte("Diameter:");
    LCD1602_write(1, 0x30 + diameter / 10 % 10);
    LCD1602_write(1, 0x30 + diameter % 10);
    LCD1602_write(0, 0xc0);

  } else if (page == 4) {
    LCD1602_write(0, 0x80);
    LCD1602_writebyte("Alarm speed:");
    LCD1602_write(1, 0x30 + speed_h / 10 % 10);
    LCD1602_write(1, 0x30 + speed_h % 10);
    LCD1602_writebyte("km/h");
    LCD1602_write(0, 0xc0);
  } else if (page == 5) {
    LCD1602_write(0, 0x80);
    LCD1602_writebyte("reservation");
  } else if (page == 6) { //保存成功的页面 定时显示2s
    LCD1602_write(0, 0x80);
    LCD1602_writebyte("Successful");
  }
}