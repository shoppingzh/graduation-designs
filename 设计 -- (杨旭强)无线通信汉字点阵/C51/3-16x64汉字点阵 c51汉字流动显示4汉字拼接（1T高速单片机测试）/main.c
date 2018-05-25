/*-----------------------------------------------
  名称：595控制4汉字点阵屏
  论坛：www.doflye.net
  编写：shifang
  日期：2009.5
  修改：无 51单片机
  内容：屏+5V、GND连接电源5V
        P0.0-P0.3分别连接A、B、C、D，用于控制16行，通过2路HC138控制
        SCK时钟连接P2.5
        LATCH锁存连接P2.6
        R1红色数据信号连接至P2.4
        G1绿色数据信号连接至P0.4，如果使用单红色屏此信号无需连接
        OE使能端一般接GND，可以用IO引脚PWM控制亮度
        或者使用此引脚控制拖尾现象。
  现象：使用高速单片机测试，比如STC12C5A60S2。4个汉字显示屏拼接，向左流动显示多句话，重复循环显示。
------------------------------------------------*/
#include<reg52.h>
#include "uart.h"

#define uchar unsigned char

sbit T_STR = P2^6;       //锁存引脚，屏上标识位STR
sbit R1    = P2^4;       //数据引脚，屏上标识R1
sbit G1    = P0^4;       //数据引脚，屏上标识G1
sbit T_CLK = P2^5;       //时钟引脚，屏上标识位CLK
sbit OE    = P2^1;       //使能引脚，屏上标识EN/OE

unsigned char MoveBitNum,MoveBitNumtemp,IncNum;//移动位数,临时移动位数，大于一个字节增加字节数
unsigned int HzNum = 0;//汉字个数
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
             向595写入一个字节 单红色
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
             向595写入两个字节 双色
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
                    延时程序
------------------------------------------------*/
void Delay(unsigned int t){
	while(--t);
}


/*-----------------------------------------------
                      主程序
------------------------------------------------*/
void main(){

unsigned char count;//16行扫描数据，范围0-15
 unsigned int i,  j;
 unsigned char temp;

	//初始化
	clear();

	uart_init();

	
	   while(1){
if(work)
{
 

 i++;
 if(i==30)//更改流动速度,1T单片机和12T单片机速度大约5-8倍，注意更改参数
   {
   i=0;
   MoveBitNum++;
 if(MoveBitNum==16)//每次移动完一个汉字大小后循环
    {
      MoveBitNum=0;
	  HzNum+=1;    //调用下一个汉字
	  if(HzNum>=word_num)//需要显示的汉字个数，包括前面的一屏空字符的个数，后面清屏的空字符不包含在内,这里是(汉字个数+4)
	     HzNum=0;   //完全显示完后循环调用
    }
  }


 Delay(30);//控制扫描频率
 for(j=0;j<5;j++) //取每个汉字的前2个字节，4个汉字组成一行，数据传输完成后锁存输出即可，这里需要多取出一个汉字作为缓冲
	{                //原来j=4，现在j=5.
	 buff[j+j]=hztest[HzNum+j][count+count];  //每次移动完一个汉字后，选择下一个汉字
	 buff[j+j+1]=hztest[HzNum+j][count+count+1];
	}

  if(MoveBitNum<8)                   //  判读移动距离是大于一个字节还是小于一个字节，因为一个字节左移右移最大只能8位
	  { IncNum=0; MoveBitNumtemp=MoveBitNum; }
  else
	  { IncNum=1; MoveBitNumtemp=MoveBitNum-8;}//大于8就减去8得到的数值还是小于8
 T_STR=0;       //锁存无效
  for(j=0;j<8;j++)          //按bit的方式移动缓冲区的内容，然后输出到595，即取出的数值每个字节左移一定的位数，
	  {                                     //后面左移出的数据整合到前面的字节中，保持数据的连续性	     
	   temp=(buff[j+IncNum]>>MoveBitNumtemp)|(buff[j+1+IncNum]<<(8-MoveBitNumtemp));//这句比较重要，需要自行拿出2个字节的数据模拟分析
       Input2Byte(temp,temp);//输出到595
	  }//8个字节传输完锁存输出
 OE = 1;
 P0=count;//用P0口的前4位控制16行，屏内部通过4-16译码器工作，循环扫描16行
 T_STR=1;      //锁存有效，此时一行的数据显示到屏上
 OE = 0;
 
 count++;
 if(count==16)
    count=0;
 }
	 }
}
