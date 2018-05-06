#ifndef _STEPPER_MOTOR_H_ 
#define _STEPPER_MOTOR_H_

#define uint unsigned int
#define SM_DIRECTION_FORWARD 1		//����
#define SM_DIRECTION_BACKWARD 0		//����
#define SM_DIRECTION_REVERSE -1 	//ת������
#define SM_DEFAULT_STEP_ANGLE 1.8f	//Ĭ�ϲ����

extern void sm_config(float step_angle);
extern void sm_init(uint dir, uint speed);
extern void sm_start();
extern void sm_stop();
extern void sm_toggle();
extern void sm_direction(uint dir);
extern void sm_speed(uint speed);

#endif

