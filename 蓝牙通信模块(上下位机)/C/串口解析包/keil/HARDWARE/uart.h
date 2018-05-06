#ifndef _UART_H_
#define _UART_H_

#include <reg52.h>
#include <stdio.h>
#define uchar unsigned char
#define uint unsigned int

extern uchar rec_data;

void uart_init(void);
void receive_byte(uchar rec_data);		//���յ����ݵĻص�����
void send_char(char send_data);
void send_string(char* str);

#endif