#ifndef _TIMER_H_
#define _TIMER_H_

#ifndef uchar
	#define uchar unsigned char
#endif
#ifndef uint
	#define uint unsigned int
#endif
#ifndef ulong
	#define ulong unsigned long
#endif

extern void timer_init();
extern void timer0_set_time(uint us);
extern void timer0_start();
extern void timer0_stop();
extern void timer0_timeout();

#endif