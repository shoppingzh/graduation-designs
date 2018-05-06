#ifndef _STEPPER_MOTOR_H_ 
#define _STEPPER_MOTOR_H_

#define uint unsigned int
#define SM_DIRECTION_FORWARD 1		//正向
#define SM_DIRECTION_BACKWARD 0		//反向
#define SM_DIRECTION_REVERSE -1 	//转换方向
#define SM_DEFAULT_STEP_ANGLE 1.8f	//默认步距角

extern void sm_config(float step_angle);
extern void sm_init(uint dir, uint speed);
extern void sm_start();
extern void sm_stop();
extern void sm_toggle();
extern void sm_direction(uint dir);
extern void sm_speed(uint speed);

#endif

