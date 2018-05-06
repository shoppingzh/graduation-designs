#include "uart.h"
#include "reg51.h"

/**
* ���ڳ�ʼ��
*/		   
void uart_init(){
	TMOD |= 0x20;
	TH1 = 0xfd;
	TL1 = 0xfd;
	SCON = 0x50;
	EA = 1;
	ES = 1;
	TR1 = 1;
}

/**
* ���ڷ������ݣ�ͬ������
*/
void uart_send(uchar dat){
	SBUF = dat;
	while(!TI);
	TI = 0;
}

/**
* ���ڽ����жϣ����յ������ݴ��͸�uart_received()�ص��������ⲿͨ������ú�����ȡ���յ�������
*/
void uart_int() interrupt 4{
	if(TI) return;
	RI = 0;
	uart_received(SBUF);
}