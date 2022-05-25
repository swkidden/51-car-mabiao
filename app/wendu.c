/*
 * @LastEditors: Dark white
 * @LastEditTime: 2022-05-25 22:41:02
 * @FilePath: \51\51-car-mabiao\app\wendu.c
 * @Description: based on ds18b20
 *
 * Copyright (c) 2022 by Dark white, All Rights Reserved.
 */
#include "wendu.h"
#include "../driver/uart.h"
#include <intrins.h>
sbit DQ = P3 ^ 7; //定义数据线
uint8 temperature = 0;
/*************精确延时函数*****************/
void delay(unsigned char i) {
  do {
    _nop_();
    _nop_();
    _nop_();
    i--;
  } while (i);
}

/*****************DS18B20******************/
void Init_Ds18b20(void) // DS18B20初始化send reset and initialization command
{
  DQ = 1;     // DQ复位,不要也可行。
  delay(1);   //稍做延时
  DQ = 0;     //单片机拉低总线
  delay(120); // 51-120精确延时，维持至少480us
  // delay(100);
  DQ = 1;
  delay(100); //释放总线，即拉高了总线
  // while(~DQ); //51-100此处延时有足够,确保能让DS18B20发出存在脉冲。
}
uint8 Read_One_Byte() //读取一个字节的数据read a byte date
                      //读数据时,数据以字节的最低有效位先从总线移出
{
  uint8 i = 0;
  uint8 dat = 0;
  for (i = 8; i > 0; i--) {
    DQ = 0;  //将总线拉低，要在1us之后释放总线
             //单片机要在此下降沿后的15us内读数据才会有效。
    _nop_(); //至少维持了1us,表示读时序开始
    dat >>= 1; //让从总线上读到的位数据，依次从高位移动到低位。
    DQ = 1; //释放总线，此后DS18B20会控制总线,把数据传输到总线上
    delay(
        1); // 51-1
            // //延时7us,此处参照推荐的读时序图，尽量把控制器采样时间放到读时序后的15us内的最后部分
    if (DQ) //控制器进行采样
    {
      dat |=
          0x80; //若总线为1,即DQ为1,那就把dat的最高位置1;若为0,则不进行处理,保持为0
    }
    delay(10); // 51-10     //此延时不能少，确保读时序的长度60us。
  }
  return (dat);
}
void Write_One_Byte(uint8 dat) {
  uint8 i = 0;
  for (i = 8; i > 0; i--) {
    DQ = 0; //拉低总线
    _nop_(); //至少维持了1us,表示写时序(包括写0时序或写1时序)开始
    DQ = dat & 0x01; //从字节的最低位开始传输
                     //指令dat的最低位赋予给总线,必须在拉低总线后的15us内,
                     //因为15us后DS18B20会对总线采样。
    delay(11); // 51-10         //必须让写时序持续至少60us
    DQ = 1;    //写完后,必须释放总线,
    dat >>= 1;
    delay(1); // 51-1
  }
}

void Get_Tmp() //获取温度get the temperature
{
  float tt;
  uint8 a, b;
  uint16 temp;
  Init_Ds18b20();       //初始化
  Write_One_Byte(0xcc); //忽略ROM指令
  Write_One_Byte(0x44); //温度转换指令
  Init_Ds18b20();       //初始化
  Write_One_Byte(0xcc); //忽略ROM指令
  Write_One_Byte(0xbe); //读暂存器指令
  a = Read_One_Byte();  //读取到的第一个字节为温度LSB
  b = Read_One_Byte();  //读取到的第二个字节为温度MSB
  temp = b;             //先把高八位有效数据赋于temp
  temp <<= 8;           //把以上8位数据从temp低八位移到高八位
  temp = temp | a;      //两字节合成一个整型变量
  if (b > 0x80) {
    temp = (~temp) + 1;
  } 
  tt = temp * 0.0625; //得到真实十进制温度值 //因为DS18B20可以精确到0.0625度
                      ////所以读回数据的最低位代表的是0.0625度
  temperature=tt;
}