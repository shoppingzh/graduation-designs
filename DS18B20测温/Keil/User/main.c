#include <reg51.h>
#include <intrins.h>
#include "ds18b20.h"
#include "uart.h"
#include "lcd1602.h"
#include "stdio.h"

#define uchar unsigned char
#define uint unsigned int

uchar temp;

void display(){
	uchar str[5];
	sprintf(str, "%d", (int)temp);	
	lcd_display_string(1, 6, str);
}

void main(){

	uchar a, b, c;
	//uart_init();
	lcd_simple_init();
	lcd_display_string(1, 1, "Temp: ");
	while(1){
		uchar t = ds18b20_read_temp1();
		if(t != temp){
			temp = t;
			display();
		}

	    /*for(c=100;c>0;c--)
	        for(b=50;b>0;b--)
	            for(a=16;a>0;a--);
	   				 _nop_();*/ 
	}


}
