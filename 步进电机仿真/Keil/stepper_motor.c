#include "stepper_motor.h"
#include "reg51.h"
#include "timer0.h"

float step_angle = SM_DEFAULT_STEP_ANGLE;		//�����
sbit sm_ena = P1^0;		//ʹ��
sbit sm_dir = P1^1;		//����
sbit sm_pul = P1^2;		//����

/**
* ����������ã����ò�������Ĳ����
*/
void sm_config(float new_step_angle){
	step_angle = new_step_angle;	
}

/**
* ���õ��ת��
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
* ���õ��ת��
*/
static void set_speed(uint speed){
	float ms;
	ms = (60 * step_angle * 1000.0) / (360.0 * speed);
	timer0_init(BIT_16_WORK_MODE, ms * 1000ul);
}

/**
* ��������ĳ�ʼ����ȷ��ת����ٶ�
*/
void sm_init(uint dir, uint speed){
	set_direction(dir);
	set_speed(speed);
}

/**
* �������
*/
void sm_start(){
	sm_ena = 1;
	timer0_start();		//������ʱ��
}

/**
* ���ֹͣ
*/
void sm_stop(){
	sm_ena = 0;
	timer0_stop();		//�رն�ʱ��
}

/**
* �л����״̬
*/
void sm_toggle(){
	sm_ena ? sm_stop() : sm_start();
}

/**
* ���õ��ת��
*/
void sm_direction(uint dir){
	sm_stop();
	set_direction(dir);
	sm_start();
}

/**
* ���õ��ת��
*/
void sm_speed(uint speed){
	sm_stop();
	set_speed(speed);
	sm_start();	
}

/**
* ��������
*/
static void give_pulse(){
	sm_pul = ~sm_pul;
}

/**
* ��ʱ����ʱʱ�䵽
*/
void on_time_out(){
	give_pulse();
}




