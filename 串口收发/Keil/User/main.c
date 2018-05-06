#include "uart.h"
#include "reg51.h"

void main(){
	int i, j, k;
	uart_init();

	while(1){
		uart_send('a');
		//for(i=0;i<20;i++)
			for(j=0;j<100;j++)
				for(k=0;k<50;k++);
	}
}

void uart_received(uchar dat){
	P1 = dat;
}