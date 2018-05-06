#ifndef _STPPER_MOTOR_H_
#define _STPPER_MOTOR_H_

#ifndef uchar
	#define uchar unsigned char
#endif
#ifndef uint
	#define uint unsigned int
#endif
#ifndef ulong
	#define ulong unsigned long
#endif
#define SM_MIN_PULSE_INTERVAL 50				//系统最小脉冲周期(us)
#define SM_DIR_FORWARD 0
#define SM_DIR_BACKWARD 1
#define SM_DIR_REVERSE 2
#define SM_X_STEP_ANGLE 1.8f
#define SM_Y_STEP_ANGLE 1.8f

extern void sm_init();
extern void sm_x_dir(uchar dir);
extern void sm_y_dir(uchar dir);
extern void sm_x_speed(uint speed);
extern void sm_y_speed(uint speed);
extern void sm_x_start();
extern void sm_y_start();
extern void sm_x_stop();
extern void sm_y_stop();
extern void sm_x_run(uint speed, uchar dir, ulong time);
extern void sm_y_run(uint speed, uchar dir, ulong time);
extern void sm_xy_run(uint xspeed, uchar xdir, uint yspeed, uchar ydir, ulong time);

#endif