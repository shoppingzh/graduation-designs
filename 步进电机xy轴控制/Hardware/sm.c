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
* ����rpm���㶨ʱʱ��
*/
static long get_time_us(uint speed){
	float ms = (60.0 * SM_STEP_ANGLE * 1000) / (360.0 * speed);
	return ms * 1000ul; 
}

/**
* ��ȡ��ȷ�Ķ�ʱʱ�䣬����ʱʱ�䳬�����ʱʱ��ʱʹ��Ĭ��ת�ٵĶ�ʱʱ��
*/
static uint get_correct_time(uint speed){
	long us = get_time_us(speed);
	if(us > 65535){
		us = get_time_us(SM_DEFAULT_SPEED);
	}
	return us;	
}

/**
* ����x�����ķ���
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
* ����y�����ķ���
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
* ����x�������ٶ�
*/
static void set_x_speed(uint speed){
	uint us = get_correct_time(speed);
	//���ö�ʱ��0�Ķ�ʱʱ��
	timer0_set_time(us);			
}

/**
* ����y�������ٶ�
*/
static void set_y_speed(uint speed){
	uint us = get_correct_time(speed);
	//���ö�ʱ��1�Ķ�ʱʱ��
	timer1_set_time(us);			
}

/**
* x������ʼ��
*/
static void sm_x_init(uchar dir, uint speed){
	set_x_dir(dir);
	set_x_speed(speed);			
}

/**
* y������ʼ��
*/
static void sm_y_init(uchar dir, uint speed){
	set_y_dir(dir);
	set_y_speed(speed);			
}

/**
* ����x����
*/
static void start_x(){
	x_sm_ena = 1;
	timer0_start();
}

/**
* ����y����
*/
static void start_y(){
	y_sm_ena = 1;
	timer1_start();
}

/**
* ֹͣx����
*/
static void stop_x(){
	x_sm_ena = 0;
	timer0_stop();
}

/**
* ֹͣy����
*/
static void stop_y(){
	y_sm_ena = 0;
	timer1_stop();	
}

/********************************API***************************************/

/**
* �����ʼ��
*/
void sm_init(){
	//��ʼ����ʱ����ʹ��������ʱ�������ж�
	timer_init();		
}

/**
* ���õ��ת��
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
* ���õ��ת��
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
* �������
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
* ֹͣ���
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
* ��ʱ��0��ʱʱ�䵽����x��������
*/
void timer0_timeout(){
	x_sm_pul = ~x_sm_pul;
}

/**
* ��ʱ��1��ʱʱ�䵽����y��������
*/
void timer1_timeout(){
	y_sm_pul = ~y_sm_pul;
}