#include "reg51.h"
#include "uart.h"

void main(){
	uart_init();
	while(1);	
}

void uart_received(uchar ch){
	uart_send(ch);	
}
