#include "lcd12864.h"


void lcd12864_delay(unsigned int n)
{
  unsigned int i;
  for(i=0; i<n; i++) {;}
}
 //���з���һ�ֽ����� 
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
//���н���һ�ֽ�����   
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
//��ȡ��־λBF
bit ReadBF(bit bf)
{
     unsigned char dat;
     SendByte(0xFA);//11111,01,0 RW=1,RS=0
     dat=ReceieveByte();
     if(dat>0x7F)bf=1;else bf=0;
     return bf;
     }
//д��������
void SendCMD(unsigned char dat)
{
     //while(ReadBF){;}
      RS_CS=1;
     SendByte(0xF8);//11111,00,0 RW=0,RS=0 ͬ����־
     SendByte(dat&0xF0);//����λ
     SendByte((dat&0x0F)<<4);//����λ
      RS_CS=0;
}
//д��ʾ���ݻ��ֽ��ַ�
void SendDat(unsigned char dat)
{
      //while(ReadBF){;}
      RS_CS=1;
     SendByte(0xFA);//11111,01,0 RW=0,RS=1
     SendByte(dat&0xF0);//����λ
     SendByte((dat&0x0F)<<4);//����λ
      RS_CS=0;
}
/*      д���ֵ�LCD ָ����λ��
     x_add��ʾRAM�ĵ�ַ
     dat1/dat2��ʾ���ֱ���
*/
void display(unsigned char x_add,unsigned char dat1,unsigned char dat2)
{
     SendCMD(x_add);//1xxx,xxxx �趨DDRAM 7λ��ַxxx,xxxx����ַ������AC
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
  SendCMD( x_add+y);//1xxx,xxxx �趨DDRAM 7λ��ַxxx,xxxx����ַ������AC
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
//��ʼ�� LCM
void initlcm(void)
{
//     RST=0;
     RS_CS=0;
//      PSB=0;//serial mode
    lcd12864_delay(100);
//     RST=1;
     SendCMD(0x30);//�������ã�һ����8λ���ݣ�����ָ�
     SendCMD(0x0C);//0000,1100  ������ʾ���α�off���α�λ��off
     SendCMD(0x01);//0000,0001 ��DDRAM
     SendCMD(0x02);//0000,0010 DDRAM��ַ��λ
     SendCMD(0x80);//1000,0000 �趨DDRAM 7λ��ַ000��0000����ַ������AC
//     SendCMD(0x04);//���趨����ʾ�ַ�/����������λ��DDRAM��ַ�� һ
//     SendCMD(0x0F);//��ʾ�趨������ʾ����ʾ��꣬��ǰ��ʾλ��������
}

//����
void clear(){
  	SendDat(0x01);
}

//���һ������
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