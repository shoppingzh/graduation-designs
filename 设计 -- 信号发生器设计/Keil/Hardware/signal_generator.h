#ifndef _SIGNAL_GENERATOR_H_
#define _SIGNAL_GENERATOR_H_

#define uchar unsigned char
#define uint unsigned int
#define CO_SYSTEM_X_SMALL_MARK 5
#define CO_SYSTEM_X_LARGE_MARK (CO_SYSTEM_X_SMALL_MARK * 2)
#define CO_SYSTEM_Y_SMALL_MARK 4
#define CO_SYSTEM_Y_LARGE_MARK (CO_SYSTEM_Y_SMALL_MARK * 2)
#define CO_SYSTEM_ORIGIN_X 3											//坐标原点在屏幕的x坐标
#define CO_SYSTEM_ORIGIN_Y 38											//坐标原点在屏幕的y坐标
#define CO_SYSTEM_X_LENGTH 125
#define CO_SYSTEM_Y_LENGTH 37
 

extern void signal_generator_init();
extern void signal_generator_quare(uint fre);
extern void signal_generator_traingle(uint fre);
extern void signal_generator_sin(uint fre);
extern void signal_generator_sawtooth(uint fre);

#endif
