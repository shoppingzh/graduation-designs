#include "timer.h"
#include "reg51.h"

static uchar th0, tl0;

/**
* 定时器初始化：使用定时器0进行定时
*/
void timer_init(){
	TMOD |= 0x21;
	//暂不赋初值
	EA = 1;
	ET0 = 1;
}

/**
* 设置定时器0的定时时间
*/
void timer0_set_time(uint us){
	th0 = (65536 - us) / 256;
	tl0 = (65536 - us) % 256;
	TH0 = th0;
	TL0 = tl0;
}

/**
* 启动定时器0
*/
void timer0_start(){
	TR0 = 1;
}

/**
* 停止定时器0
*/
void timer0_stop(){
	TR0 = 0;
}

/**
* 定时器0的中断服务程序
*/
void timer0_int() interrupt 1{
	TH0 = th0;
	TL0 = tl0;
	timer0_timeout();
}
