#include "printer.h"
#include "uart.h"

/**
* 打印器初始化
*/	
void printer_init(){
	uart_init();	
}

/**
* 打印
*/
void print(char* str){
	while(*str){
		uart_send(*str);
		str++;
	}
}