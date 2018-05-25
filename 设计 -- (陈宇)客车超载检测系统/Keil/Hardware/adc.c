#include "adc.h"
#include "reg51.h"

#define OUT P1

sbit CLK = P3^2;
sbit ST = P2^5;
sbit EOC = P2^6;
sbit OE = P2^7;

/**
* ADC0808 ��ʼ��
* ADC��ת����Ҫʱ�ӵ�֧��
*/
void adc_init(){
	TMOD |= 0x01;
	TH0 = 0xff;
	TL0 = 0xf7;
	EA = 1;
	ET0 = 1;
	TR0 = 1;
}

/**
* ADC0808 ת��
* @return ת�������ֵ����ΪADC0808��8λADC�����Է��ص���ֵ��ΧΪ��0~255
*/
uchar adc_transform(){
	uchar temp;
	ST = 0;
	ST = 1;
	ST = 0;			//����ת��
	while(!EOC);	//�ȴ�ת������
	OE = 1;
	temp = OUT;
	OE = 0;

	return temp;
}

//��ʱ��0�жϣ�����ת��ʱ��
void timer0_int() interrupt 1{
	TH0 = 0xff;
	TL0 = 0xf7;
	CLK = ~CLK;
}
