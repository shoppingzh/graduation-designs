#include "timer.h"
#include "reg51.h"

static uchar th0, tl0;

/**
* ��ʱ����ʼ����ʹ�ö�ʱ��0���ж�ʱ
*/
void timer_init(){
	TMOD |= 0x21;
	//�ݲ�����ֵ
	EA = 1;
	ET0 = 1;
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
* ������ʱ��0
*/
void timer0_start(){
	TR0 = 1;
}

/**
* ֹͣ��ʱ��0
*/
void timer0_stop(){
	TR0 = 0;
}

/**
* ��ʱ��0���жϷ������
*/
void timer0_int() interrupt 1{
	TH0 = th0;
	TL0 = tl0;
	timer0_timeout();
}
