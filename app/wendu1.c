/*
 * @LastEditors: Dark white
 * @LastEditTime: 2022-05-25 22:34:39
 * @FilePath: \51\51-car-mabiao\app\wendu1.c
 * @Description: based on dth11 目前不可正常工作 可能是传感器本身的问题待解决
 *
 * Copyright (c) 2022 by Dark white, All Rights Reserved.
 */
#include "wendu.h"
#include"../driver/uart.h"
#include <intrins.h>
sbit Data = P3 ^ 7; //定义数据线
uint8 temperature=0;
/*------------------------------------------------
 uS延时函数，含有输入参数 unsigned char t，无返回值
 unsigned char 是定义无符号字符变量，其值的范围是
 0~255 这里使用晶振12M，精确延时请使用汇编,大致延时
 长度如下 T=tx2+5 uS
------------------------------------------------*/
void DelayUs2x(unsigned char t) {
  while (--t)
    ;
}
/*------------------------------------------------
 mS延时函数，含有输入参数 unsigned char t，无返回值
 unsigned char 是定义无符号字符变量，其值的范围是
 0~255 这里使用晶振12M，精确延时请使用汇编
------------------------------------------------*/
void DelayMs(unsigned char t) {

  while (t--) {
    //大致延时1mS
    DelayUs2x(245);
    DelayUs2x(245);
  }
}
/*------------------------------------------------
              DHT11延时函数
------------------------------------------------*/
void DHT11_delay_us(uint8 n) {
  while (--n)
    ;
}

void DHT11_delay_ms(uint16 z) {
  uint16 i, j;
  for (i = z; i > 0; i--)
    for (j = 110; j > 0; j--)
      ;
}
/*------------------------------------------------
              DHT11开始信号
------------------------------------------------*/
void DHT11_start() {
  Data = 1;
  DHT11_delay_us(2);
  Data = 0;
  DHT11_delay_ms(25); //延时18ms以上
  Data = 1;
  DHT11_delay_us(30);
}
/*------------------------------------------------
              接收八位二进制
------------------------------------------------*/
uint8 DHT11_rec_byte() //接收一个字节
{
  uint8 i, dat = 0;
  for (i = 0; i < 8; i++) //从高到低依次接收8位数据
  {
    while (!Data);                 //等待50us低电平过去
    DHT11_delay_us(8); //延时60us，如果还为高则数据为1，否则为0
    dat <<= 1;     //移位使正确接收8位数据，数据为0时直接移位
    if (Data == 1) //数据为1时，使dat加1来接收数据1
      dat += 1;
    while (Data)
      ; //等待数据线拉低
  }
  return dat;
}
/*------------------------------------------------
              接收40bit数据
------------------------------------------------*/
void DHT11_receive() //接收40位的数据
{
  uint8 R_H, R_L, T_H, T_L, revise;
  DHT11_start();

  if (Data == 0) {

    while (Data == 0); //等待拉高

    DHT11_delay_us(40);        //拉高后延时80us
    R_H = DHT11_rec_byte();    //接收湿度高八位
    R_L = DHT11_rec_byte();    //接收湿度低八位
    T_H = DHT11_rec_byte();    //接收温度高八位
    T_L = DHT11_rec_byte();    //接收温度低八位
    revise = DHT11_rec_byte(); //接收校正位

    DHT11_delay_us(25); //结束

    //if ((R_H + R_L + T_H + T_L) == revise) //校正
    {
      temperature = T_H;
    }
  }
}
