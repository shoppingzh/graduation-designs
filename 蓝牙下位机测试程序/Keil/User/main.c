#include "reg51.h"
#include "uart.h"

sbit LED = P1^3;
char sendflag, c;

void main(){
	uart_init();

	while(1){
		if(sendflag){
			uart_send(c);
			sendflag = 0;
		}
	}
}

void uart_received(uchar ch){
	LED = ~LED;
	c = ch;
	sendflag = 1;
}
