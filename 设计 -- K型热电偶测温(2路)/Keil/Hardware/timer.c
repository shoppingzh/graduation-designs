#include "timer.h"
#include "reg51.h"

uchar count = 0;

/**
* 初始化定时器并启动
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
* 开启定时器
*/
void timer_start(){
	TR0 = 1;
}

/**
* 停止定时器
*/
void timer_stop(){
	TR0 = 0;
}

/**
* 1s定时时间到，调用timeout回调
*/
void timer_int() interrupt 1{
	TH0 = 0x9c;
	TL0 = 0xb0;
	timer_timeout();
}