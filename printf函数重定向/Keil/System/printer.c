#include "printer.h"
#include "uart.h"
#include "stdio.h"

/**
* 初始化
*/
void printer_init(){
	uart_init();
}

/**
* 重定向c库函数printf到串口
*/
char putchar(char c){
	uart_send(c);
	return c;	
}