#include "reg51.h"
#include "uart.h"
#include "tck_max6675.h"

#define uchar unsigned char
#define uint unsigned int

void delay(){
	uchar i, j, k;
	for(i=0;i<20;i++)
		for(j=0;j<100;j++)
			for(k=0;k<200;k++);
}

void main(){

	uart_init();
	while(1){
		uart_send(tck_read_temp());
		delay();			
	}
}
