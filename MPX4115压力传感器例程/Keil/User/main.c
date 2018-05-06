#include "reg52.h"
#include "adc.h"
#include "uart.h"
#include "intrins.h"

void delay1s(void)   //Îó²î 0us
{
    unsigned char a,b,c;
    for(c=167;c>0;c--)
        for(b=171;b>0;b--)
            for(a=16;a>0;a--);
    _nop_();  //if Keil,require use intrins.h
}


void main(){

	uart_init();

	while(1){
		uart_send(adc_transform());
		delay1s();	
	}
}
