#ifndef _STPPER_MOTOR_H_
#define _STPPER_MOTOR_H_

#define uchar unsigned char
#define uint unsigned int
#define SM_MIN_PULSE_INTERVAL 50		//X、Y轴电机最小脉冲周期
#define SM_DIR_FORWARD 0
#define SM_DIR_BACKWARD 1
#define SM_DIR_REVERSE 2
#define SM_X_STEP_ANGLE 1.8f
#define SM_Y_STEP_ANGLE 1.8f

extern void sm_init();
extern void sm_x_dir(uchar dir);
extern void sm_y_dir(uchar dir);
extern void sm_x_speed(uint s);
extern void sm_y_speed(uint s);
extern void sm_x_start();
extern void sm_y_start();	

#endif