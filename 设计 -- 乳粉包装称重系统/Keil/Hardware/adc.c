#include "adc.h"
#include "reg51.h"

#define OUT P1

sbit ST = P3^3;
sbit EOC = P3^4;
sbit OE = P3^5;

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
