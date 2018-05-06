#ifndef _TIME_H_
#define _TIME_H_

#define uchar unsigned char
#define uint unsigned int

extern void timer_init();
extern void timer0_set_time(uint us);
extern void timer1_set_time(uint us);
extern void timer0_start();
extern void timer1_start();
extern void timer0_stop();
extern void timer1_stop();
extern void timer0_timeout();
extern void timer1_timeout();


#endif