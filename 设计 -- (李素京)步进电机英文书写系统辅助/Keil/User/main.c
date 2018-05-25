#include "reg51.h"
#include "uart.h"
#define uint unsigned int

sbit pwm = P3^7;			//�����pwm�źŷ�����
uchar count;
bit flag;

void main(){
	P2 = 0xff;
	IP = 0x10;
	uart_init();	

	TMOD |= 0x01;
	TH0 = 0xfe;
	TL0 = 0x33;
	EA = 1;
	ET0 = 1;
	TR0 = 1;	

	while(1){
	
	}			
}

//�ӻ��ӵ���������ʱ��ת��״̬����ת��һ���Ƕ�
void uart_received(uchar cmd){
	flag = !flag;
}


void timer_int() interrupt 1{
	TH0 = 0xfe;
	TL0 = 0x33;
	
	if(count == 0){
		pwm = 1;
	}
		
	if(flag){
		if(count == 2){
			pwm = 0;
		}		
	}else{
		if(count == 4){
			pwm = 0;
		}
	}
	
	if(count++ >= 40){
		count = 0;
	}	
}
