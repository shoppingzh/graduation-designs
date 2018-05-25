#include "writer.h"
#include "sm.h"
#include "math.h"
#include "reg51.h"
#include "uart.h"
#include "stdio.h"

/**
* 书写系统初始化
*/
void writer_init(){
	sm_init();
	uart_init();
}

/**
* 书写
* @param x1		书写的起始点x坐标
* @param y1 	书写的起始点y坐标
* @param x2		书写的终止点x坐标
* @param y2		书写的终止点y坐标
* @param flag	是否提笔的标志位
*/
static void writer_write_line(int x1, int y1, int x2, int y2, uchar flag){
	int w = x2 - x1;								//X轴书写距离(mm)
	int h = y2 - y1;								//Y轴书写距离(mm)
	float s = sqrt(w * w + h * h);					//书写总距离(mm)
	uint t = (ulong)(s * 1000.0f) / WRITE_SPEED;	//书写总时长(ms)
	float vx = abs(w) * 1000.0 / t;					//X轴的书写速度(mm/s)
	float vy = abs(h) * 1000.0 / t;					//Y轴的书写速度(mm/s)	
	uint rpmx = vx * 60.0 / MM_PER_REV;				//X轴的书写速度(转/分钟)
	uint rpmy = vy * 60.0 / MM_PER_REV;				//Y轴的书写速度(转/分钟)

	//打印调试信息
	if(DEBUG){
		printf("------------------------START------------------------\n");
		printf("Run: (%d, %d) -> (%d, %d) \n", x1, y1, x2, y2);
		printf("Pen Status: %s\n", (flag == 0 ? "No Action" : (flag == 1 ? "Down Action" : "Up Action")));
		printf("X Distance: %dmm \n", (int)w);
		printf("Y Distance: %dmm \n", (int)h);
		printf("Total Distance: %.3fmm \n", s);
		printf("Total Time: %dms \n", (int)t);
		printf("X Speed: %.3fmm/s \n", vx);
		printf("Y Speed: %.3fmm/s \n", vy);
		printf("X RPM: %dr/min \n", (int)rpmx);
		printf("Y RPM: %dr/min \n", (int)rpmy);
		printf("X RPM(ajusted): %dr/min \n", (int)(rpmx * K_RPM));
		printf("Y RPM(ajusted): %dr/min \n", (int)(rpmy * K_RPM));
		printf("-------------------------END------------------------\n\n");
	}
	
	//是否提笔或下笔
	if(flag != 0){
		ET0 = 0;
		uart_send(CMD_CHANGE_FLAG);
		ET0 = 1;
	}

	//电机工作
	sm_xy_run(rpmx * K_RPM, (w > 0 ? SM_DIR_BACKWARD : SM_DIR_FORWARD),
			  rpmy * K_RPM, (h > 0 ? SM_DIR_BACKWARD : SM_DIR_FORWARD),
			  t * K_TIME);
}

/*
* 书写一个字符
* @param coor		字符的编码信息，存储格式[x坐标, y坐标, 笔的动作(提笔/下笔/无动作), ... ]
* @param len		字符编码数组的长度 
*/
void writer_write(uchar coor[], uint len){
	uint i;
	writer_write_line(0, 0, coor[0], coor[1], 0);		//第一笔：(0, 0)到起始点，悬空移动
	for(i=0;i<len - 4;i+=3){
		writer_write_line(coor[i], coor[i+1], coor[i+3], coor[i+4], coor[i+2]);	
	}
	writer_write_line(coor[len-3], coor[len-2], 0, 0, coor[len-1]);
}

//重定向printf函数
char putchar(char c){
	uart_send(c);
	return c;
}
