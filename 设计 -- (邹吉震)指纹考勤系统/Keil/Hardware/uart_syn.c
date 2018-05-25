#include "uart_syn.h"
#include "reg51.h"

/**
* ���ڳ�ʼ��
*/		   
void uart_init(){
	TMOD |= 0x20;
	TH1 = 0xfd;
	TL1 = 0xfd;
	SCON = 0x50;
	TR1 = 1;
}

/**
* �������ݣ�ͬ������
*/
void uart_send(uchar dat){
	SBUF = dat;
	while(!TI);
	TI = 0;
}

/**
* �������ݣ�ͬ�����գ�ֱ�����ճɹ��ŷ�������
*/
uchar uart_receive(){
	while(!RI);
	RI = 0;
	return SBUF;
}