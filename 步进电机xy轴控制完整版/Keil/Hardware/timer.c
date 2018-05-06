#include "timer.h"
#include "reg51.h"

static uchar th0, tl0, th1, tl1;

/**
* 定时器初始化：使用两个定时器，两个定时器都使用方式1，并且都开中断
*/
void timer_init(){
	TMOD = 0x11;
	//暂不赋初值
	EA = 1;
	ET0 = 1;
	ET1 = 1;
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
* 设置定时器1的定时时间
*/
void timer1_set_time(uint us){
	th1 = (65536 - us) / 256;
	tl1 = (65536 - us) % 256;
	TH1 = th1;
	TL1 = tl1;		
}

/**
* 启动定时器0
*/
void timer0_start(){
	TR0 = 1;
}

/**
* 启动定时器1
*/
void timer1_start(){
	TR1 = 1;
}

/**
* 停止定时器0
*/
void timer0_stop(){
	TR0 = 0;
}

/**
* 停止定时器1
*/
void timer1_stop(){
	TR1 = 0;
}

/**
* 定时器0的中断服务程序
*/
void timer0_int() interrupt 1{
	TH0 = th0;
	TL0 = tl0;
	timer0_timeout();
}

/**
* 定时器1的中断服务程序
*/
void timer1_int() interrupt 3{
	TH1 = th1;
	TL1 = tl1;
	timer1_timeout();
}
