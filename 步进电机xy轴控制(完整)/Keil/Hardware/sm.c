#include "sm.h"
#include "reg51.h"
#include "timer.h"

sbit x_ena = P1^0;
sbit x_dir = P1^1;
sbit x_pul = P1^2;
sbit y_ena = P1^3;
sbit y_dir = P1^4;
sbit y_pul = P1^5;

uint x_count, y_count, x_max_count, y_max_count;	//X轴计数、Y轴计数、X轴最大计数、Y轴最大计数

/**************************************************************************/
/******************************* API **************************************/
/**************************************************************************/

/**
* 电机系统初始化：
*	1. 确定X轴、Y轴电机的初始转向
*	2. 确定X轴、Y轴电机的初始速度
*	3. 初始化定时器，同时使用两个定时器；X、Y轴电机同时使用定时器0作为脉冲发生器，定时器1用于普通计时
*/
void sm_init(){
	sm_x_dir(SM_DIR_FORWARD);
	sm_y_dir(SM_DIR_FORWARD);

	timer_init();
	timer0_set_time(SM_MIN_PULSE_INTERVAL);			//X、Y轴电机的脉冲产生最小周期为SM_MIN_PULSE_INTERVAL
	timer1_set_time(50 * 1000ul);					//普通计时的最小周期为50ms
	timer0_start();									//电机系统启动，定时器0开始工作，以后都不会停止			
}

/**
* 调整X轴电机的转向
*	1. SM_DIR_FORWARD：顺时针转动
*	2. SM_DIR_BACKWARD：逆时针转动
*	3. SM_DIR_REVERSE：转变转向，如果当前为顺时针，则调整至逆时针，反之亦然
*/
void sm_x_dir(uchar dir){
	if(dir == SM_DIR_FORWARD){
		x_dir = 0;
	}else if(dir == SM_DIR_BACKWARD){
		x_dir = 1;
	}else if(dir == SM_DIR_REVERSE){
		x_dir = ~x_dir;
	}		
}

/**
* 调整Y轴电机的转向
*	1. SM_DIR_FORWARD：顺时针转动
*	2. SM_DIR_BACKWARD：逆时针转动
*	3. SM_DIR_REVERSE：转变转向，如果当前为顺时针，则调整至逆时针，反之亦然
*/
void sm_y_dir(uchar dir){
	if(dir == SM_DIR_FORWARD){
		y_dir = 0;
	}else if(dir == SM_DIR_BACKWARD){
		y_dir = 1;
	}else if(dir == SM_DIR_REVERSE){
		y_dir = ~y_dir;
	}		
}

/**
* 设置X轴电机的转速
* 给定的参数s为rpm即电机每分钟转动的圈数，通过给定rpm得出电机的脉冲宽度
*/
void sm_x_speed(uint s){
	float ms = (60.0 * SM_X_STEP_ANGLE * 1000) / (360.0 * s);		//根据速度计算出脉冲宽度
	long us = ms * 1000ul;
	x_count = 0;
	x_max_count = us / SM_MIN_PULSE_INTERVAL;		
}

/**
* 设置Y轴电机的转速
* 给定的参数s为rpm即电机每分钟转动的圈数，通过给定rpm得出电机的脉冲宽度
*/
void sm_y_speed(uint s){
	float ms = (60.0 * SM_Y_STEP_ANGLE * 1000) / (360.0 * s);		//根据速度计算出脉冲宽度
	long us = ms * 1000ul;
	y_count = 0;
	y_max_count = us / SM_MIN_PULSE_INTERVAL;		
}

/**
* 启动X轴电机
*/
void sm_x_start(){
	x_ena = 1;		
}

/**
* 启动Y轴电机
*/
void sm_y_start(){
	y_ena = 1;		
}

/**
* 定时器0定时时间到，该函数将被定时器0自动回调，请不要调用
*/
void timer0_timeout(){
	if(x_count++ >= x_max_count){		//Y轴的脉冲时间到
		x_pul = ~x_pul;
		x_count = 0;
	}

	if(y_count++ >= y_max_count){		//Y轴的脉冲时间到
		y_pul = ~y_pul;
		y_count = 0;
	}			
}
