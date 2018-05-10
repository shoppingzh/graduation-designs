#include "reg51.h"
#include "lcd1602.h"
#include "adc.h"
#include "intrins.h"
#include "stdio.h"

#define uchar unsigned char
#define uint unsigned int

char idx = 0;
code uchar cs[] = {0xfc, 0xf9, 0xf3, 0xf6};

sbit led_add = P3^6;
sbit led_addend = P3^7;

//ת��
void roll(){
	if(idx >= 4){
		idx = 0;
	}
	P2 = cs[idx++];
}

//��ʱ1
void delay100ms(void) {
    uchar a,b,c;
    for(c=19;c>0;c--)
        for(b=20;b>0;b--)
            for(a=130;a>0;a--);
}

//��ʱ2
void delay1s(void){
    uchar a,b,c;
    for(c=167;c>0;c--)
        for(b=171;b>0;b--)
            for(a=16;a>0;a--);
    _nop_(); 
}


void main(){
	int i;
	lcd_simple_init();

	while(1){

		char t;
		uchar weight;
		char str[5];

		led_add = 1;
		led_addend = 1;

		/*****************�����̷۹�*****************/
		lcd_display_string(1, 1, "1. Delivery pot");
		lcd_display_string(2, 1, "time: 0s");
		//�����̷۹޵ĵ������3s
		for(i=0;i<31;i++){
			//��ʾ����ʱ��
			if((i != 0) && ((t = i % 10) == 0)){
				lcd_display_string(2, 1, "time: ");
				lcd_display_char(2, 7, (i/10)+48);
				lcd_display_char(2, 8, 's');
			}
	
			//ת�����
			roll();
			delay100ms();
		}
	
		//�̷۹޵�λ
		delay1s();
		lcd_clear();
		lcd_display_string(2, 1, "--Delivery End--");
	
		/*****************�����̷�*****************/
		delay1s();
		lcd_clear();
		lcd_display_string(1, 1, "2. Putting milk");
		led_add = 0;
		led_addend = 1;
		while(1){
			roll();
			delay100ms();

			//��������ת��
			adc_transform();
			adc_transform();
			adc_transform();

			weight = adc_transform();
			lcd_display_string(2, 1, "weight: ");
			sprintf(str, "%3d", (int)weight);
			lcd_display_string(2, 9, str);
	
			//�������
			if(weight == 163){
				lcd_clear();
				lcd_display_string(2, 1, "--Putting End--");
				led_add = 1;
				led_addend = 0;
				break;				
			}
		}
	
		/*****************�̷۹ް�װ*****************/
		delay1s();
		lcd_clear();
		lcd_display_string(1, 1, "3. Packing pot");
		for(i=0;i<20;i++){
			roll();
			delay100ms();
		}
		lcd_clear();
		lcd_display_string(2, 1, "--Packing End--");

		delay1s();
		lcd_clear();
		lcd_display_string(2, 1, "-----All End----");
	
	
		//��ͣ3sѭ��ִ��
		delay1s();
		delay1s();
		delay1s();
		lcd_clear();		
	}
}
