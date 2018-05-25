#include "signal_generator.h"
#include "lcd12864.h"

#define SQU_N 63
#define TRA_N 63
#define SIN_N 75
#define SAW_N 31


code uchar square[] = {31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 
						0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
code uchar tra[] = {31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0,
					0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};
code uchar sin[] = {16, 15, 14, 13, 12, 11, 10,  9,  8,  7,  6,  5,  4,  3,  3,  2,  1,  1,  0, 
					 0,  1,  1,  2,  3,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16,
					17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 30, 31, 32, 32, 33,
					33, 32, 32, 31, 30, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17
					};
code uchar saw[] = {31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};


uchar x, idx, n = TRA_N;	//X轴坐标和当前数组索引
uchar *arr = tra;

void delay(uint t){
	uint i, j;
	for(i=0;i<t;i++)
		for(j=0;j<110;j++);
}

/**
* 绘制坐标系
*/
static void draw_coordinate_system(){
	uchar i, j=1;
	//绘制x轴
	for(i=CO_SYSTEM_ORIGIN_Y;i>=(CO_SYSTEM_ORIGIN_Y - CO_SYSTEM_Y_LENGTH);i--){
		lcd_draw_point(CO_SYSTEM_ORIGIN_X, i);
		//绘制y轴小刻度
		if(j % CO_SYSTEM_Y_SMALL_MARK == 0){
			lcd_draw_point(CO_SYSTEM_ORIGIN_X + 1, i);	
		}
		//绘制y轴大刻度
		if(j++ % CO_SYSTEM_Y_LARGE_MARK == 0){
			lcd_draw_point(CO_SYSTEM_ORIGIN_X + 2, i);	
		}	
	}

	//绘制x轴
	for(i=CO_SYSTEM_ORIGIN_X;i<(CO_SYSTEM_ORIGIN_X + CO_SYSTEM_X_LENGTH);i++){
		lcd_draw_point(i, CO_SYSTEM_ORIGIN_Y);
		
		//绘制x轴小刻度
		if((i-CO_SYSTEM_ORIGIN_X) % CO_SYSTEM_X_SMALL_MARK == 0){
			lcd_draw_point(i, CO_SYSTEM_ORIGIN_Y - 1);	
		}
		//绘制x轴大刻度
		if((i-CO_SYSTEM_ORIGIN_X) % CO_SYSTEM_X_LARGE_MARK == 0){
			lcd_draw_point(i, CO_SYSTEM_ORIGIN_Y - 2);
		}
	}
}

/**
* 信号发生器初始化
*/
void signal_generator_init(){
	lcd_init();
	draw_coordinate_system();
}

/**
* 绘制普通波形，该函数将显示arr所表示的波形
* @param fre	频率
* @param tozero 一个波形绘制完，是否拉到0
*/
static void signal_generator_wave(uint fre, uchar tozero){
	uchar i;
	lcd_write_com(0x01);
	draw_coordinate_system();

	idx = 0;
	x = 0;
	while(1){
		//画完一个波形
		if(idx >= n){
		   	idx = 0;
			if(tozero){
				for(i=0;i<31;i++){
					lcd_draw_point(x + 4, i);
				}			
			}
		}

		lcd_draw_point(x + 5, arr[idx += fre]);
		
		//画完一帧
		if(x >= 127 - 5){
			break;
		}
		x += 1;	
	}			
}

/**
* 方波
*/
void signal_generator_quare(uint fre){
	arr = square;
	n = SQU_N;
	signal_generator_wave(fre, 0);		
}

/**
* 三角波
*/
void signal_generator_traingle(uint fre){
	arr = tra;
	n = TRA_N;
	signal_generator_wave(fre, 0);		
}

/**
* 正弦波
*/
void signal_generator_sin(uint fre){
	arr = sin;
	n = SIN_N;
	signal_generator_wave(fre, 0);
}

/**
* 锯齿波
*/
void signal_generator_sawtooth(uint fre){
	arr = saw;
	n = SAW_N;
	signal_generator_wave(fre, 0);	
}

