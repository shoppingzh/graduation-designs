#ifndef _TIME0_H_
#define _TIME0_H_

#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long

#define WORK_MODE_0 0
#define WORK_MODE_1 1
#define WORK_MODE_2 2
#define WORK_MODE_3 3
#define BIT_13_WORK_MODE WORK_MODE_0		//13λ��ʱ��
#define BIT_16_WORK_MODE WORK_MODE_1		//16λ��ʱ��
#define RELOAD_BIT_8_WORK_MODE WORK_MODE_2	//�Զ���װ8λ��ʱ��
#define BIT_8_WORK_MODE WORK_MODE_3			//����8λ��ʱ��
#define DEFAULT_WORK_MODE BIT_16_WORK_MODE
#define MIN_PRECISION 500					//��С���ȣ�500΢��

extern void timer0_init(uchar work_mode, ulong us);
extern void timer0_start();
extern void timer0_stop();
extern void on_time_out();


#endif