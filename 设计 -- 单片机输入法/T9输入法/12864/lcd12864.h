#ifndef _LCD12864_H
#define _LCD12864_H
#include <reg52.h>
sbit E_CLK =P3^6;//clock input                    同步时钟输入端			 
sbit RW_SID=P3^7;//data input/output            串行数据输入、输出端
sbit RS_CS =P3^5;//chip select                    片选端
//sbit PSB   =P3^6;//serial mode select            串口模式
//sbit RST   =P1^2;
void lcd12864_delay(unsigned int n);
void SendByte(unsigned char dat);
unsigned char ReceieveByte(void);
bit ReadBF(bit bf);
void SendCMD(unsigned char dat);
void SendDat(unsigned char dat);
void display(unsigned char x_add,unsigned char dat1,unsigned char dat2);
void displaystring(	unsigned char x,unsigned char y ,unsigned char *p);
void initlcm(void);
void clear();
void clearline(unsigned char line);
#endif