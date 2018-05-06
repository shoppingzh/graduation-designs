#ifndef _SM_H_
#define _SM_H_

#define uchar unsigned char
#define uint unsigned int
#define SM_STEP_ANGLE 1.8f
#define SM_DEFAULT_SPEED 300
#define SM_X 0
#define SM_Y 1
#define SM_DIR_FORWARD 0
#define SM_DIR_BACKWARD 1
#define SM_DIR_REVERSE 2

extern void sm_init();
extern void sm_dir(uchar sm, uchar dir);
extern void sm_speed(uchar sm, uint speed);
extern void sm_start(uchar sm);
extern void sm_stop(uchar sm);


#endif