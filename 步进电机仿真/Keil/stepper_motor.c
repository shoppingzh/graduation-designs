#include "stepper_motor.h"
#include "reg51.h"
#include "timer0.h"

float step_angle = SM_DEFAULT_STEP_ANGLE;		//步距角
sbit sm_ena = P1^0;		//使能
sbit sm_dir = P1^1;		//方向
sbit sm_pul = P1^2;		//脉冲

/**
* 步进电机配置：设置步进电机的步距角
*/
void sm_config(float new_step_angle){
	step_angle = new_step_angle;	
}

/**
* 设置电机转向
*/
static void set_direction(uint dir){
	if(dir == SM_DIRECTION_FORWARD){
		sm_dir = 0;		
	}else if(dir == SM_DIRECTION_BACKWARD){
		sm_dir = 1;
	}else{
		sm_dir = ~sm_dir;	
	}
}

/*
* 设置电机转速
*/
static void set_speed(uint speed){
	float ms;
	ms = (60 * step_angle * 1000.0) / (360.0 * speed);
	timer0_init(BIT_16_WORK_MODE, ms * 1000ul);
}

/**
* 步进电机的初始化：确定转向和速度
*/
void sm_init(uint dir, uint speed){
	set_direction(dir);
	set_speed(speed);
}

/**
* 电机启动
*/
void sm_start(){
	sm_ena = 1;
	timer0_start();		//启动定时器
}

/**
* 电机停止
*/
void sm_stop(){
	sm_ena = 0;
	timer0_stop();		//关闭定时器
}

/**
* 切换电机状态
*/
void sm_toggle(){
	sm_ena ? sm_stop() : sm_start();
}

/**
* 设置电机转向
*/
void sm_direction(uint dir){
	sm_stop();
	set_direction(dir);
	sm_start();
}

/**
* 设置电机转速
*/
void sm_speed(uint speed){
	sm_stop();
	set_speed(speed);
	sm_start();	
}

/**
* 给出脉冲
*/
static void give_pulse(){
	sm_pul = ~sm_pul;
}

/**
* 定时器定时时间到
*/
void on_time_out(){
	give_pulse();
}




