#include "timer0.h"
#include "reg51.h"

static uchar reload, th0, tl0;
static ulong t_count = 0;
static ulong max_count;

/**
* 16λ��ʱ���ĳ�ʼ��
*/
static void bit_16_init(ulong us){
	reload = 0;
	TMOD = 0x01;
	if(us <= 65535){
		max_count = 1;
		th0 = (65536 - us) / 256;
		tl0 = (65536 - us) % 256;
		TH0 = th0;
		TL0 = tl0;
	}else{
		max_count = us / MIN_PRECISION;
		th0 = (65536 - MIN_PRECISION) / 256;
		tl0 = (65536 - MIN_PRECISION) % 256;
		TH0 = th0;
		TL0 = tl0;
	}
}

/**
* ��ʱ��0�ĳ�ʼ������ѡ��ʽ1�ͷ�ʽ2��������ģʽ����Ҫ����һ����ʱʱ�䣨΢�
*/
void timer0_init(uchar work_mode, ulong us){
	switch(work_mode){
		case BIT_16_WORK_MODE:
			bit_16_init(us);
			break;
		case RELOAD_BIT_8_WORK_MODE:
			//TODO
			break;
		default:
			bit_16_init(us);
			break;
	}
	
	EA = 1;
	ET0 = 1;
}

/**
* ������ʱ��
*/
void timer0_start(){
	TR0 = 1;
}

/**
* ֹͣ��ʱ��
*/
void timer0_stop(){
	t_count = 0;
	TR0 = 0;
}

/**
* ��ʱ��0�жϷ������
*/
void timer0_int() interrupt 1{
	if(!reload){
		TH0 = th0;
		TL0 = tl0;
	}

	if(t_count++ >= max_count){
		t_count = 0;
		on_time_out();
	}
}
