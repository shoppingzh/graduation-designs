#include "timer.h"
#include "reg51.h"

uchar count = 0;

/**
* ��ʼ����ʱ��������
*/
void timer_init(){
	TMOD = 0x01;
	TH0 = 0x9c;
	TL0 = 0xb0;
	EA = 1;
	ET0 = 1;
	TR0 = 1;
}

/**
* ������ʱ��
*/
void timer_start(){
	TR0 = 1;
}

/**
* ֹͣ��ʱ��
*/
void timer_stop(){
	TR0 = 0;
}

/**
* 1s��ʱʱ�䵽������timeout�ص�
*/
void timer_int() interrupt 1{
	TH0 = 0x9c;
	TL0 = 0xb0;
	timer_timeout();
}