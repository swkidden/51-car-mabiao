#include "LCD1602.h"
sbit LCD1602_rs=P2^7;//IO ����
sbit LCD1602_rw=P2^6;
sbit LCD1602_e=P2^5;


void LCD1602_delay(uint T)					  //��ʱ����
{
	while(T--);
}

/********************************************************************
* ���� : LCD1602_write(uchar order,dat)
* ���� : 1602д�����ݺ���
* ���� : orderΪ����/�����л����� //0������ 1������
*	: datΪ����/����ķ�������
* ��� : ��
***********************************************************************/
void LCD1602_write(uchar order,dat)				  //1602 һ���ֽ�  ����
{
    LCD1602_e=0;
    LCD1602_rs=order;
    LCD1602_dat=dat;
    LCD1602_rw=0;
    LCD1602_e=1;
    LCD1602_delay(1);
    LCD1602_e=0;																								     
}
/********************************************************************
* ���� : LCD1602_writebye(uchar *prointer)
* ���� : 1602д�����ݺ���  ָ��ʽ
* ���� : ������Ҫ��ʾ������
* ��� : ��
***********************************************************************/
void LCD1602_writebyte(uchar *prointer)				   //1602 �ַ���    ����
{
    while(*prointer!='\0')
    {
        LCD1602_write(1,*prointer);
        prointer++;
    }
}
/********************************************************************
* ���� : LCD1602_cls()
* ���� : ��ʼ��1602Һ�� 
* ���� : ��
* ��� : ��
***********************************************************************/
void LCD1602_cls()									 //1602 ��ʼ��
{
	LCD1602_write(0,0x01);     //1602 ���� ָ��
	LCD1602_delay(1500);
	LCD1602_write(0,0x38);     // �������� 8λ��5*7����
	LCD1602_delay(1500);
	LCD1602_write(0,0x0c);     //���� ���   ����ʾ���ء�����ʾ��ꡢ�ַ�����˸
	LCD1602_write(0,0x06);
	LCD1602_write(0,0xd0);
	LCD1602_delay(1500);
}