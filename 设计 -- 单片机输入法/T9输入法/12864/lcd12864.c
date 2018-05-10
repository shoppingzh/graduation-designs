#include "lcd12864.h"


void lcd12864_delay(unsigned int n)
{
  unsigned int i;
  for(i=0; i<n; i++) {;}
}
 //串行发送一字节数据 
void SendByte(unsigned char dat)
{
     unsigned char i;
     for(i=0;i<8;i++)
           {
                 E_CLK=0;
                 if(dat&0x80)RW_SID=1;else RW_SID=0;
                 E_CLK=1;
                 dat=dat<<1;
            }
}
//串行接收一字节数据   
unsigned char ReceieveByte(void)
{
     unsigned char i,d1,d2;
     for(i=0;i<8;i++)
           {
                 E_CLK=0;lcd12864_delay(100);
                 E_CLK=1;
                 if(RW_SID)d1++;
                 d1=d1<<1;
            }
     for(i=0;i<8;i++)
           {
                 E_CLK=0;lcd12864_delay(100);
                 E_CLK=1;
                 if(RW_SID)d2++;
                 d2=d2<<1;
            }
     return (d1&0xF0+d2&0x0F);
}
//读取标志位BF
bit ReadBF(bit bf)
{
     unsigned char dat;
     SendByte(0xFA);//11111,01,0 RW=1,RS=0
     dat=ReceieveByte();
     if(dat>0x7F)bf=1;else bf=0;
     return bf;
     }
//写控制命令
void SendCMD(unsigned char dat)
{
     //while(ReadBF){;}
      RS_CS=1;
     SendByte(0xF8);//11111,00,0 RW=0,RS=0 同步标志
     SendByte(dat&0xF0);//高四位
     SendByte((dat&0x0F)<<4);//低四位
      RS_CS=0;
}
//写显示数据或单字节字符
void SendDat(unsigned char dat)
{
      //while(ReadBF){;}
      RS_CS=1;
     SendByte(0xFA);//11111,01,0 RW=0,RS=1
     SendByte(dat&0xF0);//高四位
     SendByte((dat&0x0F)<<4);//低四位
      RS_CS=0;
}
/*      写汉字到LCD 指定的位置
     x_add显示RAM的地址
     dat1/dat2显示汉字编码
*/
void display(unsigned char x_add,unsigned char dat1,unsigned char dat2)
{
     SendCMD(x_add);//1xxx,xxxx 设定DDRAM 7位地址xxx,xxxx到地址计数器AC
     SendDat(dat1);
     SendDat(dat2);
}
void displaystring(	unsigned char x,unsigned char y ,unsigned char *p)
{
unsigned char  x_add;
switch(x)
{
case  0:	x_add=0x80;break;
case  1:	x_add=0x90;break;
case  2:	x_add=0x88;break;
case  3:	x_add=0x98;break;
}

while(*p!='\0')
{   
  SendCMD( x_add+y);//1xxx,xxxx 设定DDRAM 7位地址xxx,xxxx到地址计数器AC
  SendDat(*p++);   
  SendDat(*p++);
  y++; 
  if(y==8)
  {
  switch(x_add)
    {
      case  0x80:	x_add=0x90;break;
      case  0x90:	x_add=0x88;break;
      case  0x88:	x_add=0x98;break;
      case  0x98:	x_add=0x80;break;
    }
   y=0;
  }
 }
}
//初始化 LCM
void initlcm(void)
{
//     RST=0;
     RS_CS=0;
//      PSB=0;//serial mode
    lcd12864_delay(100);
//     RST=1;
     SendCMD(0x30);//功能设置，一次送8位数据，基本指令集
     SendCMD(0x0C);//0000,1100  整体显示，游标off，游标位置off
     SendCMD(0x01);//0000,0001 清DDRAM
     SendCMD(0x02);//0000,0010 DDRAM地址归位
     SendCMD(0x80);//1000,0000 设定DDRAM 7位地址000，0000到地址计数器AC
//     SendCMD(0x04);//点设定，显示字符/光标从左到右移位，DDRAM地址加 一
//     SendCMD(0x0F);//显示设定，开显示，显示光标，当前显示位反白闪动
}

//清屏
void clear(){
  	SendDat(0x01);
}

//清除一行内容
void clearline(unsigned char line){
	displaystring(line, 0, "    ");
	displaystring(line, 1, "    ");
	displaystring(line, 2, "    ");
	displaystring(line, 3, "    ");
	displaystring(line, 4, "    ");
	displaystring(line, 5, "    ");
	displaystring(line, 6, "    ");		
	displaystring(line, 7, "    ");
}