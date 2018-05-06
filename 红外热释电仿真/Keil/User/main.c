#include "reg51.h"
#include "adc.h"
#include "lcd1602.h"
#include "stdio.h"

#define cal(ad) ((1.0f / (ad * 0.0005f + 0.00158f)) - 7)

uchar v;

void display(){
	uchar str[16];
	lcd_clear();
	sprintf(str, "Distance: %.2fm", cal(v));
	lcd_display_string(1, 1, str);	
}

void main(){
	adc_init();
	lcd_simple_init();
	
	while(1){
		uchar temp = adc_transform();
		if(temp != v){
			v = temp;
			display();
		}
	}
}
