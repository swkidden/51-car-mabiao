/*
 * @LastEditors: Dark white
 * @LastEditTime: 2022-05-26 11:45:09
 * @FilePath: \51-car-mabiao\app\key_task.c
 * @Description:
 *
 * Copyright (c) 2022 by Dark white, All Rights Reserved.
 */
#include "key_task.h"
#include "../driver/LCD1602.h"
#include "../src/c51.h"
#include "../driver/eeprom52.h"
void key_regesiter() {
  switch (Key_scan()) {
  case flag_left:
    if (page > 0&&page<6) {
      page--;
      LCD1602_write(0, 0x01);
    }
    break;
  case flag_up:
    switch (page) {
    case 3:
      if (diameter < 99) {
        diameter++;
      }
      break;
    case 4:
      if (speed_h < 99) {
        speed_h++;
      }
      break;
    case 5:
      write_memory();
      page=6;
    default:
      break;
    }
    break;
  case flag_down:
    switch (page) {
    case 3:
      if (diameter > 0) {
        diameter--;
      }
      break;
    case 4:
      if (speed_h > 0) {
        speed_h--;
      }
    default:
      break;
    }
    break;
  case flag_right:
    if (page < 5) {
      page++;
      LCD1602_write(0, 0x01);
    }
    break;
  default:
    break;
  }
}
void write_memory() {
  SectorErase(0x2000);
  byte_write(0x2000,speed_h );
  byte_write(0x2001,diameter );
  byte_write(0x2002,mileage );
}

 void read_memory() {
  speed_h =  byte_read(0x2000);
  if (speed_h > 99||speed_h<0) {
    speed_h = 0;
  }
  diameter =  byte_read(0x2001);
  if (diameter > 99||diameter<0) {
    diameter = 0;
  }
  mileage =  byte_read(0x2002);
  if (mileage > 99||mileage<0) {
    mileage = 99;
  }
}