#include "printer.h"
#include "uart.h"
#include "stdio.h"

/**
* ��ʼ��
*/
void printer_init(){
	uart_init();
}

/**
* �ض���c�⺯��printf������
*/
char putchar(char c){
	uart_send(c);
	return c;	
}