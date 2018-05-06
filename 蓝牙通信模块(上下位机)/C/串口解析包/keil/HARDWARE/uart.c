#include "uart.h"

uchar rec_data = 0;

//���ڳ�ʼ�� cb���������ݵĻص�
void uart_init(){
	TMOD = 0x20;
	TH1 = 0xfd;
	TL1 = 0xfd;
	SCON = 0x50;
	EA =  1;
	ES = 1;
	TR1 = 1;
}

//���ڷ���һ���ַ�
void send_char(char send_data){
	SBUF = send_data;
	while(!TI);
	TI = 0;	
}

//���ڷ����ַ���
void send_string(char* str){
	while(*str){
		send_char(*str);
		str++;
	}
}


void uart_int(void) interrupt 4{
	if(TI) return;
	RI = 0;
	rec_data = SBUF;
	receive_byte(rec_data);
}