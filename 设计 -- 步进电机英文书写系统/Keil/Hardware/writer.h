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

#define WRITE_SPEED 10.0f			//书写速度(mm/s)
#define MM_PER_REV 5				//电机每转前进的距离(mm)
#define DEBUG 0						//是否开启调试模式，请在仿真时开启，实物测试时切不可开启！
#define K_TIME 1/3.3f				//时间比例系数
#define K_RPM 7.071f				//RPM比例系数
#define CMD_CHANGE_FLAG 0x10       	//切换状态命令

extern void writer_init();
//extern void writer_write(int x1, int y1, int x2, int y2, uchar state);
extern void writer_write(uchar coor[], uint len);

#endif