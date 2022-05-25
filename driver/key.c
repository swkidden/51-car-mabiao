/*
 * @LastEditors: Dark white
 * @LastEditTime: 2022-05-24 00:07:32
 * @FilePath: \mabiao\driver\key.c
 * @Description:
 *
 * Copyright (c) 2022 by Dark white, All Rights Reserved.
 */
#include "key.h"
uint8 key_scan() {
  if (KEY_DOWN == 0) {
    while (!KEY_DOWN);
    return flag_down;
  }
  if (KEY_UP == 0) {
    while (!KEY_UP);
    return flag_up;
  }
  if (KEY_LEFT == 0) { 
    while (!KEY_LEFT);
    return flag_left;
  }
  if (KEY_RIGHT == 0) {
    while (!KEY_RIGHT);
    return flag_right;
  }
}