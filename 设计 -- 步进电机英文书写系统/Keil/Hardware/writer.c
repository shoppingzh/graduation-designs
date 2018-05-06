#include "writer.h"
#include "sm.h"
#include "math.h"
#include "reg51.h"
#include "uart.h"
#include "stdio.h"

/**
* ��дϵͳ��ʼ��
*/
void writer_init(){
	sm_init();
	uart_init();
}

/**
* ��д
* @param x1		��д����ʼ��x����
* @param y1 	��д����ʼ��y����
* @param x2		��д����ֹ��x����
* @param y2		��д����ֹ��y����
* @param flag	�Ƿ���ʵı�־λ
*/
static void writer_write_line(int x1, int y1, int x2, int y2, uchar flag){
	int w = x2 - x1;								//X����д����(mm)
	int h = y2 - y1;								//Y����д����(mm)
	float s = sqrt(w * w + h * h);					//��д�ܾ���(mm)
	uint t = (ulong)(s * 1000.0f) / WRITE_SPEED;	//��д��ʱ��(ms)
	float vx = abs(w) * 1000.0 / t;					//X�����д�ٶ�(mm/s)
	float vy = abs(h) * 1000.0 / t;					//Y�����д�ٶ�(mm/s)	
	uint rpmx = vx * 60.0 / MM_PER_REV;				//X�����д�ٶ�(ת/����)
	uint rpmy = vy * 60.0 / MM_PER_REV;				//Y�����д�ٶ�(ת/����)

	//��ӡ������Ϣ
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
	
	//�Ƿ���ʻ��±�
	if(flag != 0){
		ET0 = 0;
		uart_send(CMD_CHANGE_FLAG);
		ET0 = 1;
	}

	//�������
	sm_xy_run(rpmx * K_RPM, (w > 0 ? SM_DIR_BACKWARD : SM_DIR_FORWARD),
			  rpmy * K_RPM, (h > 0 ? SM_DIR_BACKWARD : SM_DIR_FORWARD),
			  t * K_TIME);
}

/*
* ��дһ���ַ�
* @param coor		�ַ��ı�����Ϣ���洢��ʽ[x����, y����, �ʵĶ���(���/�±�/�޶���), ... ]
* @param len		�ַ���������ĳ��� 
*/
void writer_write(uchar coor[], uint len){
	uint i;
	writer_write_line(0, 0, coor[0], coor[1], 0);		//��һ�ʣ�(0, 0)����ʼ�㣬�����ƶ�
	for(i=0;i<len - 4;i+=3){
		writer_write_line(coor[i], coor[i+1], coor[i+3], coor[i+4], coor[i+2]);	
	}
	writer_write_line(coor[len-3], coor[len-2], 0, 0, coor[len-1]);
}

//�ض���printf����
char putchar(char c){
	uart_send(c);
	return c;
}
