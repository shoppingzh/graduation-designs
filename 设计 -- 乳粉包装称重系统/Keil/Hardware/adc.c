#include "adc.h"
#include "reg51.h"

#define OUT P1

sbit ST = P3^3;
sbit EOC = P3^4;
sbit OE = P3^5;

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
