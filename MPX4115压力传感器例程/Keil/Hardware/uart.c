#include "uart.h"
#include "reg51.h"

/**
* 串口初始化
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
* 串口发送数据：同步发送
*/
void uart_send(uchar dat){
	SBUF = dat;
	while(!TI);
	TI = 0;
}

/**
* 串口接收中断，接收到的数据传送给uart_received()回调函数，外部通过定义该函数获取接收到的数据
*/
void uart_int() interrupt 4{
	if(TI) return;
	RI = 0;
	uart_received(SBUF);
}