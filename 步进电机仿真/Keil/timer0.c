#include "timer0.h"
#include "reg51.h"

static uchar reload, th0, tl0;
static ulong t_count = 0;
static ulong max_count;

/**
* 16位定时器的初始化
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
* 定时器0的初始化：可选择方式1和方式2两个工作模式，需要给定一个定时时间（微妙）
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
* 启动定时器
*/
void timer0_start(){
	TR0 = 1;
}

/**
* 停止定时器
*/
void timer0_stop(){
	t_count = 0;
	TR0 = 0;
}

/**
* 定时器0中断服务程序
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
