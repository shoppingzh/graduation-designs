/*-----------------------------------------------
  ���ƣ�595����4���ֵ�����
  ��̳��www.doflye.net
  ��д��shifang
  ���ڣ�2009.5
  �޸ģ��� 51��Ƭ��
  ���ݣ���+5V��GND���ӵ�Դ5V
        P0.0-P0.3�ֱ�����A��B��C��D�����ڿ���16�У�ͨ��2·HC138����
        SCKʱ������P2.5
        LATCH��������P2.6
        R1��ɫ�����ź�������P2.4
        G1��ɫ�����ź�������P0.4�����ʹ�õ���ɫ�����ź���������
        OEʹ�ܶ�һ���GND��������IO����PWM��������
        ����ʹ�ô����ſ�����β����
  ����ʹ�ø��ٵ�Ƭ�����ԣ�����STC12C5A60S2��4��������ʾ��ƴ�ӣ�����������ʾ��仰���ظ�ѭ����ʾ��
------------------------------------------------*/
#include<reg52.h>
#include "uart.h"

#define uchar unsigned char

sbit T_STR = P2^6;       //�������ţ����ϱ�ʶλSTR
sbit R1    = P2^4;       //�������ţ����ϱ�ʶR1
sbit G1    = P0^4;       //�������ţ����ϱ�ʶG1
sbit T_CLK = P2^5;       //ʱ�����ţ����ϱ�ʶλCLK
sbit OE    = P2^1;       //ʹ�����ţ����ϱ�ʶEN/OE

unsigned char MoveBitNum,MoveBitNumtemp,IncNum;//�ƶ�λ��,��ʱ�ƶ�λ��������һ���ֽ������ֽ���
unsigned int HzNum = 0;//���ָ���
unsigned char buff[10];

uchar xdata hztest[20][32];
uchar word_num = 0;

static void clear(){
	uchar k, s;
	for(s=0;s<100;s++){
		for(k=0;k<32;k++){
			hztest[s][k] = 0;
		}
	}
}

uchar word = 0;
uchar idx = 0;
uchar last;
bit work = 0;

void uart_received(uchar dat){
//	unsigned char k, s;	
//	for(s=0;s<8;s++){
//		
//		for(k=0;k<32;k++){
//			hztest[s][k] = ff[s][k];
//		}
//		
//	}

	if(last == 0x55 && dat == 0xaa){
		work = 1;
	}
	if(last == 0xaa && dat == 0x55){
		work = 0;
		word = 0;
		idx = 0;
		word_num = 0;

		clear();
	}
		

	last = dat;

	hztest[word][idx++] = dat;
	if(idx >= 32){
		idx = 0;
		word++;
		word_num++;
	}
}


/*-----------------------------------------------
             ��595д��һ���ֽ� ����ɫ
------------------------------------------------*/
void InputByte( unsigned  char DataR1){ 
	unsigned char i;
	for(i=8; i>0; i--){
		R1 = !(DataR1&0x01);                   
		T_CLK = 0;
		T_CLK = 1;
		DataR1 = DataR1 >> 1; 
	} 
}
/*-----------------------------------------------
             ��595д�������ֽ� ˫ɫ
------------------------------------------------*/
void Input2Byte( unsigned  char DataR1,unsigned  char DataG1){ 
	unsigned  char i;
	for(i=8; i>0; i--){
		R1 = !(DataR1&0x01);    
		G1 = !(DataG1&0x01);                
		T_CLK = 0;
		T_CLK = 1;
		DataR1 = DataR1 >> 1; 
		DataG1 = DataG1 >> 1; 
	} 
}


/*-----------------------------------------------
                    ��ʱ����
------------------------------------------------*/
void Delay(unsigned int t){
	while(--t);
}


/*-----------------------------------------------
                      ������
------------------------------------------------*/
void main(){

unsigned char count;//16��ɨ�����ݣ���Χ0-15
 unsigned int i,  j;
 unsigned char temp;

	//��ʼ��
	clear();

	uart_init();

	
	   while(1){
if(work)
{
 

 i++;
 if(i==30)//���������ٶ�,1T��Ƭ����12T��Ƭ���ٶȴ�Լ5-8����ע����Ĳ���
   {
   i=0;
   MoveBitNum++;
 if(MoveBitNum==16)//ÿ���ƶ���һ�����ִ�С��ѭ��
    {
      MoveBitNum=0;
	  HzNum+=1;    //������һ������
	  if(HzNum>=word_num)//��Ҫ��ʾ�ĺ��ָ���������ǰ���һ�����ַ��ĸ��������������Ŀ��ַ�����������,������(���ָ���+4)
	     HzNum=0;   //��ȫ��ʾ���ѭ������
    }
  }


 Delay(30);//����ɨ��Ƶ��
 for(j=0;j<5;j++) //ȡÿ�����ֵ�ǰ2���ֽڣ�4���������һ�У����ݴ�����ɺ�����������ɣ�������Ҫ��ȡ��һ��������Ϊ����
	{                //ԭ��j=4������j=5.
	 buff[j+j]=hztest[HzNum+j][count+count];  //ÿ���ƶ���һ�����ֺ�ѡ����һ������
	 buff[j+j+1]=hztest[HzNum+j][count+count+1];
	}

  if(MoveBitNum<8)                   //  �ж��ƶ������Ǵ���һ���ֽڻ���С��һ���ֽڣ���Ϊһ���ֽ������������ֻ��8λ
	  { IncNum=0; MoveBitNumtemp=MoveBitNum; }
  else
	  { IncNum=1; MoveBitNumtemp=MoveBitNum-8;}//����8�ͼ�ȥ8�õ�����ֵ����С��8
 T_STR=0;       //������Ч
  for(j=0;j<8;j++)          //��bit�ķ�ʽ�ƶ������������ݣ�Ȼ�������595����ȡ������ֵÿ���ֽ�����һ����λ����
	  {                                     //�������Ƴ����������ϵ�ǰ����ֽ��У��������ݵ�������	     
	   temp=(buff[j+IncNum]>>MoveBitNumtemp)|(buff[j+1+IncNum]<<(8-MoveBitNumtemp));//���Ƚ���Ҫ����Ҫ�����ó�2���ֽڵ�����ģ�����
       Input2Byte(temp,temp);//�����595
	  }//8���ֽڴ������������
 OE = 1;
 P0=count;//��P0�ڵ�ǰ4λ����16�У����ڲ�ͨ��4-16������������ѭ��ɨ��16��
 T_STR=1;      //������Ч����ʱһ�е�������ʾ������
 OE = 0;
 
 count++;
 if(count==16)
    count=0;
 }
	 }
}
