#include "reg51.h"
#include "uart.h"
#include "adc.h"
#include "intrins.h"
#include "stdio.h"

void delay(){
	uchar a, b, c;
	for(c=167;c>0;c--)
        for(b=171;b>0;b--)
            for(a=16;a>0;a--);
   				 _nop_();
}

//MAIN
void main(){

	uchar temp;

	uart_init();
	adc_init();

	while(1){
		temp = adc_transform();
		printf("Transform: %d | ", (int)temp);
	 	printf("VOL: %.3fV \n", (temp / 255.0 * 5));
		delay();	
	} 


}

char putchar (char ch){
	uart_send(ch);
	return ch;
}

