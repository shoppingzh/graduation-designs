#include "sm.h"
#include "reg51.h"
#include "timer.h"

sbit x_sm_ena = P1^0;
sbit x_sm_dir = P1^1;
sbit x_sm_pul = P1^2;
sbit y_sm_ena = P1^3;
sbit y_sm_dir = P1^4;
sbit y_sm_pul = P1^5;

/**
* 根据rpm计算定时时间
*/
static long get_time_us(uint speed){
	float ms = (60.0 * SM_STEP_ANGLE * 1000) / (360.0 * speed);
	return ms * 1000ul; 
}

/**
* 获取正确的定时时间，当定时时间超出最大定时时间时使用默认转速的定时时间
*/
static uint get_correct_time(uint speed){
	long us = get_time_us(speed);
	if(us > 65535){
		us = get_time_us(SM_DEFAULT_SPEED);
	}
	return us;	
}

/**
* 设置x轴电机的方向
*/
static void set_x_dir(uchar dir){
	if(dir == SM_DIR_FORWARD){
		x_sm_dir = 0;
	}else if(dir == SM_DIR_BACKWARD){
		x_sm_dir = 1;
	}else if(dir == SM_DIR_REVERSE){
		x_sm_dir = ~x_sm_dir;
	}else{
		//do nothing
	}
}

/**
* 设置y轴电机的方向
*/
static void set_y_dir(uchar dir){
	if(dir == SM_DIR_FORWARD){
		y_sm_dir = 0;
	}else if(dir == SM_DIR_BACKWARD){
		y_sm_dir = 1;
	}else if(dir == SM_DIR_REVERSE){
		y_sm_dir = ~y_sm_dir;
	}else{
		//do nothing
	}
}

/**
* 设置x轴电机的速度
*/
static void set_x_speed(uint speed){
	uint us = get_correct_time(speed);
	//设置定时器0的定时时间
	timer0_set_time(us);			
}

/**
* 设置y轴电机的速度
*/
static void set_y_speed(uint speed){
	uint us = get_correct_time(speed);
	//设置定时器1的定时时间
	timer1_set_time(us);			
}

/**
* x轴电机初始化
*/
static void sm_x_init(uchar dir, uint speed){
	set_x_dir(dir);
	set_x_speed(speed);			
}

/**
* y轴电机初始化
*/
static void sm_y_init(uchar dir, uint speed){
	set_y_dir(dir);
	set_y_speed(speed);			
}

/**
* 启动x轴电机
*/
static void start_x(){
	x_sm_ena = 1;
	timer0_start();
}

/**
* 启动y轴电机
*/
static void start_y(){
	y_sm_ena = 1;
	timer1_start();
}

/**
* 停止x轴电机
*/
static void stop_x(){
	x_sm_ena = 0;
	timer0_stop();
}

/**
* 停止y轴电机
*/
static void stop_y(){
	y_sm_ena = 0;
	timer1_stop();	
}

/********************************API***************************************/

/**
* 电机初始化
*/
void sm_init(){
	//初始化定时器：使用两个定时器及其中断
	timer_init();		
}

/**
* 设置电机转向
*/
void sm_dir(uchar sm, uchar dir){
	if(sm == SM_X){
		set_x_dir(dir);
	}else if(sm == SM_Y){
		set_y_dir(dir);
	}else{
		//do nothing
	}
}

/**
* 设置电机转速
*/
void sm_speed(uchar sm, uint speed){
	if(sm == SM_X){
		set_x_speed(speed);
	}else if(sm == SM_Y){
		set_y_speed(speed);
	}else{
		//do nothing
	}
}

/**
* 启动电机
*/					  
void sm_start(uchar sm){
 	if(sm == SM_X){
		start_x();
	}else if(sm == SM_Y){
		start_y();
	}else{
		//do nothing
	}
}

/**
* 停止电机
*/					  
void sm_stop(uchar sm){
	if(sm == SM_X){
		stop_x();
	}else if(sm == SM_Y){
		stop_y();
	}else{
		//do nothing
	}
}

/**************************TIMER**********************************/

/**
* 定时器0定时时间到：给x轴电机脉冲
*/
void timer0_timeout(){
	x_sm_pul = ~x_sm_pul;
}

/**
* 定时器1定时时间到：给y轴电机脉冲
*/
void timer1_timeout(){
	y_sm_pul = ~y_sm_pul;
}