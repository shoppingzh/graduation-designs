#include "uart.h"

uchar rec_data = 0;

//串口初始化 cb：接收数据的回调
void uart_init(){
	TMOD = 0x20;
	TH1 = 0xfd;
	TL1 = 0xfd;
	SCON = 0x50;
	EA =  1;
	ES = 1;
	TR1 = 1;
}

void uart_int(void) interrupt 4{
	if(TI) return;
	RI = 0;
	rec_data = SBUF;
	receive_byte(rec_data);
}