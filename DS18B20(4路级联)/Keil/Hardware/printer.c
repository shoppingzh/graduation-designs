#include "printer.h"
#include "uart.h"

/**
* ��ӡ����ʼ��
*/	
void printer_init(){
	uart_init();	
}

/**
* ��ӡ
*/
void print(char* str){
	while(*str){
		uart_send(*str);
		str++;
	}
}