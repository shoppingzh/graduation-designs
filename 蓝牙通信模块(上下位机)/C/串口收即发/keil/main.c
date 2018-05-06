/**
bug：当发送过程中有数据发送过来时，会错过接收数据，因为此时串口中断已被关闭
改进方法为不关闭串口中断，而是在串口中断程序中判断是否为发送中断，如果为发送中断，直接返回即可
*/
#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int

void uart_init(void);
void send(uchar);

uchar rec_data;
bit send_flag = 0;	//发送标志位

void main(void){
	uart_init();
	while(1){
		if(send_flag){
			//关闭串口中断，以防发送完毕触发中断
			ES = 0;
			send(rec_data);
			ES = 1;
			send_flag = 0;
		}
	}	
}

//串口初始化：波特率9600，中断允许
void uart_init(void){
	TMOD = 0x20;
	TH1 = 0xfd;
	TL1 = 0xfd;
	SCON = 0x50;
	EA = 1;
	ES = 1;
	TR1 = 1;
}

//串口发送
void send(uchar dat){
	SBUF = dat;
	while(!TI);
	TI = 0;	
}

void uart_int() interrupt 4{
	RI = 0;
   	rec_data = SBUF;
	send_flag = 1;
}
