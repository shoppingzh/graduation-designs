#include<reg51.h>
#include<intrins.h>
typedef unsigned char uchar;
typedef unsigned int uint;
#define out P3				 /*数码管输出数据的端口*/

void delay(unsigned char i);    /*延迟函数1，延迟时间为5us*/
void delay1ms(unsigned int ms);	/*延迟函数2*/
void init_ds18b20();			/*DS18B20的初始化程序*/
uchar readbyte();				/*读数据*/
uchar readtemp();

sbit smg1=P1^0;				 /*数码管的位选端口*/
sbit smg2=P1^1;  			 /*数码管的位选端口*/	
sbit DQ=P2^0;				 /*与DS18B20温度传感器交换数据的端口*/

unsigned char code led[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};	   /*数码管显示0~9的代码，这里用的是共阳的，共阴与共阳之和为0xff*/

void main()
{
	uchar i;
	uchar temp;
	temp=readtemp();				   /*读取温度*/
	delay1ms(1000);
	while(1)
	{
		temp=readtemp();				  /*再次读取温度*/
		for(i=0;i<10;i++)
		{
			out=led[temp/10];		  /*获取温度的十位信息，0~9一一和上面的数码管显示代码0~9对应*/
			smg1=1;
			smg2=0;
			delay(200);				 /*延迟一下，便于清楚显示*/
			out=0xff;				/*显示一位数据后，把数码管关短，否则仿真的时候会出现问题，真实电路中不需要关断*/
			out=led[temp%10];
			smg1=0;
			smg2=1;
			delay(200);
			out=0xff;
		}
	}
}

void delay(unsigned char i)
{
	do
	{
		_nop_();				/*延迟函数，不做任何操作，只是消耗时间，这个函数在intrins.h中，所以我们之前预处理了两个.h文件*/
		_nop_();
		_nop_();
		i--;
	}while(i);
}

void init_ds18b20()
{
	uchar x=0;
	DQ=1;		  /*首先先拉高电平，为复位做准备*/
	delay(10);	  /*延迟一下*/
	DQ=0;		  /*将电平拉低，延迟至少480us*/
	delay(120);	  /*一次为5us,此处延迟600us，足以等待存在脉冲*/
	DQ=1;		  /*复位信号给出后，将电平拉高，等待获取存在脉冲*/
	delay(16);	  /*延迟15~60us,此处延迟90us，足以给存在脉冲时间*/
	x=DQ;		  /*读取存在脉冲*/
	delay(80);	  /*读取存在脉冲，存在脉冲至少为60us到240us的低电平信号，这里给出400us*/
	DQ=1;		  /*读取后，将信号复位，DS18B20初始化，数据交换协议生成*/
	P0 = x;
}

uchar readbyte()   /*读数据操作*/
{
	uchar i=0;
	uchar date=0;
	for(i=8;i>0;i--)	/*读取数据时，是一位一位的读取，因为至少有8位，所以需要循环8次*/
	{
		DQ=0;				/*数据线拉成低电平，表示读数据的开始*/
		delay(1);			/*读数据时，需要低电平保持至少1us*/
		DQ=1;				/*释放数据总线*/
		date>>=1;			/*一位一位的保存读取到的数据，所以需要移位处理*/
		if(DQ)				/*读取数据的高电平*/
			date|=0x80;			/*与操作一下，得到我们需要的数据，读取数据需要在15us内读取，这样才能保证读取的数据是正确的*/
		delay(11);
	}
	return(date);		/*返回最终的结果*/
}

void writebyte(uchar dat)
{
	uchar i=0;
	for(i=8;i>0;i--)		 /*一位一位的发送数据，和串口通信类似，读取数据也是一位一位的读取*/
	{
		DQ=0;
		DQ=dat&0x01;			  /*移位指令用来发送数据，最低位为要发送的数据*/
		delay(12);				  /*延迟，等待数据发送完毕，发送数据时间应该在45us内完成，我们延迟了60us*/
		DQ=1;
		dat>>=1;
		delay(5);
	}
}

uchar readtemp()
{
	uchar templ,temph,tt;
	uint t;
	init_ds18b20();		   /*读取数据时，先初始化设备*/
	writebyte(0XCC);	   /*因为我们是一个单片机和一个DS18B20连接，故在对ROM指令操作时，选择0xCC跳过ROM指令，不对ROM编码作出反应*/
	writebyte(0x44);	   /*RAM操作中的温度转换指令，将转换的温度存入RAM的1,2地址*/
	init_ds18b20();		   /*初始化*/
	writebyte(0xcc);	   /*同上*/
	writebyte(0xbe);	   /*从RAM中读取数据，从0地址读到9地址*/
	templ=readbyte();	   /*从DS18B20中读取温度数据中低八位*/
	temph=readbyte();	   /*从DS18B20中读取温度数据中的高八位，温度数据由16位数据组成*/
	t=temph;
	t<<=8;
	t=t|templ;
	tt=t*0.0625;		   /*真实温度的转换*/
	return(tt);			   /*返回真实可用的温度给main函数，用于显示*/
}

void delay1ms(unsigned int ms)		  /*纯延迟函数*/
{
	unsigned int i,j;
	for(i=0;i<ms;i++)
	   for(j=0;j<110;j++);
}