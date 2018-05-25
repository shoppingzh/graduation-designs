#include "sm.h"
#include "reg51.h"
#include "timer.h"

sbit x_ena = P1^0;
sbit x_dir = P1^1;
sbit x_pul = P1^2;
sbit y_ena = P1^3;
sbit y_dir = P1^4;
sbit y_pul = P1^5;

uint x_count = 0, y_count = 0;					//X�������Y�����
int x_max_count = -1, y_max_count = -1; 		//X����������Y�������� 	
ulong count = 0;								//���м���
long max_count = -1;							//����������
uchar running = 0;								//�Ƿ�������

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
	sm_x_stop();
	sm_y_stop();
	sm_x_dir(SM_DIR_FORWARD);
	sm_y_dir(SM_DIR_FORWARD);
	
	timer_init();
	timer0_set_time(SM_MIN_PULSE_INTERVAL);				//X��Y���������������С����ΪSM_MIN_PULSE_INTERVAL
	timer0_start();	
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
	float ms, us;
	if(s == 0)
		return;

 	ms = (60.0 * SM_X_STEP_ANGLE * 1000) / (360.0 * s);		//�����ٶȼ����������
	us = ms * 1000ul;
	x_count = 0;
	x_max_count = us / SM_MIN_PULSE_INTERVAL;		
}

/**
* ����Y������ת��
* �����Ĳ���sΪrpm�����ÿ����ת����Ȧ����ͨ������rpm�ó������������
*/
void sm_y_speed(uint s){
	float ms, us;
	if(s == 0)
		return;

	ms = (60.0 * SM_Y_STEP_ANGLE * 1000) / (360.0 * s);		//�����ٶȼ����������
	us = ms * 1000ul;
	y_count = 0;
	y_max_count = us / SM_MIN_PULSE_INTERVAL;		
}

/**
* ����X����
*/
void sm_x_start(){										//���ϵͳ��������ʱ��0��ʼ����
	x_ena = 1;			
}

/**
* ����Y����
*/
void sm_y_start(){										//���ϵͳ��������ʱ��0��ʼ����	
	y_ena = 1;		
}

/**
* ֹͣX����
*/
void sm_x_stop(){
	x_ena = 0;
}

/**
* ֹͣY����
*/
void sm_y_stop(){
	y_ena = 0;
}

/**
* ָ��X��������һ��ʱ��
* @param speed		X����ת��
* @param dir		X����ת��
* @param time		X��������ʱ�䣬��λ�����루ms��
*/
void sm_x_run(uint speed, uchar dir, ulong time){
	if(speed == 0)		//ת��Ϊ0����ԭ�ز���
		return;

	sm_x_speed(speed);
	sm_x_dir(dir);
	count = 0;
	max_count = time * 1000ul / SM_MIN_PULSE_INTERVAL;
	
	sm_x_start();
	running = 1;
	while(running);
	sm_x_stop();		
}

/**
* ָ��Y��������һ��ʱ��
* @param speed		Y����ת��
* @param dir		Y����ת��
* @param time		Y��������ʱ�䣬��λ�����루ms��
*/
void sm_y_run(uint speed, uchar dir, ulong time){
	if(speed == 0)
		return;

	sm_y_speed(speed);
	sm_y_dir(dir);
	count = 0;
	max_count = time * 1000ul / SM_MIN_PULSE_INTERVAL;
	
	sm_y_start();
	running = 1;
	while(running);
	sm_y_stop();		
}

/**
* ָ��X��Y�����ͬ����һ��ʱ��
* @param xspeed 	X����ת��
* @param xdir 		X����ת��
* @param yspeed 	Y����ת��
* @param ydir 		Y����ת��
* @param time 		X��Y������ͬ���е�ʱ�䣬��λ������(ms)
*/
void sm_xy_run(uint xspeed, uchar xdir, uint yspeed, uchar ydir, ulong time){
	//�������в���
	sm_x_speed(xspeed);
	sm_x_dir(xdir);
	sm_y_speed(yspeed);
	sm_y_dir(ydir);
	count = 0;
	max_count = time * 1000ul / SM_MIN_PULSE_INTERVAL;		//��ʱ����

	//�������
	if(xspeed != 0)
		sm_x_start();	
	if(yspeed != 0)
		sm_y_start();
	
	running = 1;
	while(running);		//�ȴ����н���
	sm_x_stop();		//������ֹͣ�������
	sm_y_stop();			
}

/**
* ��ʱ��0��ʱʱ�䵽���ú���������ʱ��0�Զ��ص����벻Ҫ����
*/
void timer0_timeout(){
	//X�������ʱ�䵽
	if(x_count++ >= x_max_count){		
		x_pul = ~x_pul;
		x_count = 0;
	}

	//Y�������ʱ�䵽
	if(y_count++ >= y_max_count){		
		y_pul = ~y_pul;
		y_count = 0;
	}

	//��ʱ���ڵ�����ʾ�ý׶ε����н���
	if(count++ >= max_count){
		count = 0;
		running = 0;
	}				
}

