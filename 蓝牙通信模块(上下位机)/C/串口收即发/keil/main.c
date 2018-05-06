/**
bug�������͹����������ݷ��͹���ʱ�������������ݣ���Ϊ��ʱ�����ж��ѱ��ر�
�Ľ�����Ϊ���رմ����жϣ������ڴ����жϳ������ж��Ƿ�Ϊ�����жϣ����Ϊ�����жϣ�ֱ�ӷ��ؼ���
*/
#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int

void uart_init(void);
void send(uchar);

uchar rec_data;
bit send_flag = 0;	//���ͱ�־λ

void main(void){
	uart_init();
	while(1){
		if(send_flag){
			//�رմ����жϣ��Է�������ϴ����ж�
			ES = 0;
			send(rec_data);
			ES = 1;
			send_flag = 0;
		}
	}	
}

//���ڳ�ʼ����������9600���ж�����
void uart_init(void){
	TMOD = 0x20;
	TH1 = 0xfd;
	TL1 = 0xfd;
	SCON = 0x50;
	EA = 1;
	ES = 1;
	TR1 = 1;
}

//���ڷ���
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
