#ifndef _UART_H_
#define _UART_H_

#include <reg52.h>
#include <stdio.h>
#define uchar unsigned char
#define uint unsigned int

extern uchar rec_data;

void uart_init(void);
void receive_byte(uchar rec_data);		//接收到数据的回调函数
void send_char(char send_data);
void send_string(char* str);

#endif