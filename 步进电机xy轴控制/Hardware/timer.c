#include "timer.h"
#include "reg51.h"

static uchar th0, tl0, th1, tl1;

/**
* ��ʱ����ʼ����ʹ��������ʱ����������ʱ����ʹ�÷�ʽ1�����Ҷ����ж�
*/
void timer_init(){
	TMOD = 0x11;
	//�ݲ�����ֵ
	EA = 1;
	ET0 = 1;
	ET1 = 1;
}

/**
* ���ö�ʱ��0�Ķ�ʱʱ��
*/
void timer0_set_time(uint us){
	th0 = (65536 - us) / 256;
	tl0 = (65536 - us) % 256;
	TH0 = th0;
	TL0 = tl0;
}

/**
* ���ö�ʱ��1�Ķ�ʱʱ��
*/
void timer1_set_time(uint us){
	th1 = (65536 - us) / 256;
	tl1 = (65536 - us) % 256;
	TH1 = th1;
	TL1 = tl1;		
}

/**
* ������ʱ��0
*/
void timer0_start(){
	TR0 = 1;
}

/**
* ������ʱ��1
*/
void timer1_start(){
	TR1 = 1;
}

/**
* ֹͣ��ʱ��0
*/
void timer0_stop(){
	TR0 = 0;
}

/**
* ֹͣ��ʱ��1
*/
void timer1_stop(){
	TR1 = 0;
}

/**
* ��ʱ��0���жϷ������
*/
void timer0_int() interrupt 1{
	TH0 = th0;
	TL0 = tl0;
	timer0_timeout();
}

/**
* ��ʱ��1���жϷ������
*/
void timer1_int() interrupt 3{
	TH1 = th1;
	TL1 = tl1;
	timer1_timeout();
}
