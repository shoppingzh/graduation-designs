#include "adc.h"
#include "reg51.h"

#define OUT P1

sbit CLK = P2^0;
sbit ST = P2^1;
sbit EOC = P2^2;
sbit OE = P2^3;

/**
* ADC0808 初始化
* ADC的转换需要时钟的支持
*/
void adc_init(){
	/*TMOD |= 0x01;
	TH0 = 0xf1;
	TL0 = 0x9a;
	EA = 1;
	ET0 = 1;
	TR0 = 1;*/
}

/**
* ADC0808 转换
* @return 转换后的数值，因为ADC0808是8位ADC，所以返回的数值范围为：0~255
*/
uchar adc_transform(){
	uchar temp;
	ST = 0;
	ST = 1;
	ST = 0;			//启动转换
	while(!EOC);	//等待转换结束
	OE = 1;
	temp = OUT;
	OE = 0;

	return temp;
}

//定时器0中断：产生转换时钟
void timer0_int() interrupt 1{
	TH0 = 0xf1;
	TL0 = 0x9a;
	CLK = ~CLK;
}
