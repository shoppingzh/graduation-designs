#include "sm.h"
#include "reg51.h"
#include "timer.h"

sbit x_ena = P1^0;
sbit x_dir = P1^1;
sbit x_pul = P1^2;
sbit y_ena = P1^3;
sbit y_dir = P1^4;
sbit y_pul = P1^5;

uint x_count, y_count, x_max_count, y_max_count;	//X�������Y�������X����������Y��������

/**************************************************************************/
/******************************* API **************************************/
/**************************************************************************/

/**
* ���ϵͳ��ʼ����
*	1. ȷ��X�ᡢY�����ĳ�ʼת��
*	2. ȷ��X�ᡢY�����ĳ�ʼ�ٶ�
*	3. ��ʼ����ʱ����ͬʱʹ��������ʱ����X��Y����ͬʱʹ�ö�ʱ��0��Ϊ���巢��������ʱ��1������ͨ��ʱ
*/
void sm_init(){
	sm_x_dir(SM_DIR_FORWARD);
	sm_y_dir(SM_DIR_FORWARD);

	timer_init();
	timer0_set_time(SM_MIN_PULSE_INTERVAL);			//X��Y���������������С����ΪSM_MIN_PULSE_INTERVAL
	timer1_set_time(50 * 1000ul);					//��ͨ��ʱ����С����Ϊ50ms
	timer0_start();									//���ϵͳ��������ʱ��0��ʼ�������Ժ󶼲���ֹͣ			
}

/**
* ����X������ת��
*	1. SM_DIR_FORWARD��˳ʱ��ת��
*	2. SM_DIR_BACKWARD����ʱ��ת��
*	3. SM_DIR_REVERSE��ת��ת�������ǰΪ˳ʱ�룬���������ʱ�룬��֮��Ȼ
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
* ����Y������ת��
*	1. SM_DIR_FORWARD��˳ʱ��ת��
*	2. SM_DIR_BACKWARD����ʱ��ת��
*	3. SM_DIR_REVERSE��ת��ת�������ǰΪ˳ʱ�룬���������ʱ�룬��֮��Ȼ
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
* ����X������ת��
* �����Ĳ���sΪrpm�����ÿ����ת����Ȧ����ͨ������rpm�ó������������
*/
void sm_x_speed(uint s){
	float ms = (60.0 * SM_X_STEP_ANGLE * 1000) / (360.0 * s);		//�����ٶȼ����������
	long us = ms * 1000ul;
	x_count = 0;
	x_max_count = us / SM_MIN_PULSE_INTERVAL;		
}

/**
* ����Y������ת��
* �����Ĳ���sΪrpm�����ÿ����ת����Ȧ����ͨ������rpm�ó������������
*/
void sm_y_speed(uint s){
	float ms = (60.0 * SM_Y_STEP_ANGLE * 1000) / (360.0 * s);		//�����ٶȼ����������
	long us = ms * 1000ul;
	y_count = 0;
	y_max_count = us / SM_MIN_PULSE_INTERVAL;		
}

/**
* ����X����
*/
void sm_x_start(){
	x_ena = 1;		
}

/**
* ����Y����
*/
void sm_y_start(){
	y_ena = 1;		
}

/**
* ��ʱ��0��ʱʱ�䵽���ú���������ʱ��0�Զ��ص����벻Ҫ����
*/
void timer0_timeout(){
	if(x_count++ >= x_max_count){		//Y�������ʱ�䵽
		x_pul = ~x_pul;
		x_count = 0;
	}

	if(y_count++ >= y_max_count){		//Y�������ʱ�䵽
		y_pul = ~y_pul;
		y_count = 0;
	}			
}
