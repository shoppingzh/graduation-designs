#include "uart_syn.h"
#include "reg51.h"

/**
* 串口初始化
*/		   
void uart_init(){
	TMOD |= 0x20;
	TH1 = 0xfd;
	TL1 = 0xfd;
	SCON = 0x50;
	TR1 = 1;
}

/**
* 发送数据：同步发送
*/
void uart_send(uchar dat){
	SBUF = dat;
	while(!TI);
	TI = 0;
}

/**
* 接收数据：同步接收，直到接收成功才返回数据
*/
uchar uart_receive(){
	while(!RI);
	RI = 0;
	return SBUF;
}