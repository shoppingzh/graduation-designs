#ifndef _WRITER_H_
#define	_WRITER_H_

#ifndef uchar
	#define uchar unsigned char
#endif
#ifndef uint
	#define uint unsigned int
#endif
#ifndef ulong
	#define ulong unsigned long
#endif

#define WRITE_SPEED 10.0f			//��д�ٶ�(mm/s)
#define MM_PER_REV 5				//���ÿתǰ���ľ���(mm)
#define DEBUG 0						//�Ƿ�������ģʽ�����ڷ���ʱ������ʵ�����ʱ�в��ɿ�����
#define K_TIME 1/3.3f				//ʱ�����ϵ��
#define K_RPM 7.071f				//RPM����ϵ��
#define CMD_CHANGE_FLAG 0x10       	//�л�״̬����

extern void writer_init();
//extern void writer_write(int x1, int y1, int x2, int y2, uchar state);
extern void writer_write(uchar coor[], uint len);

#endif