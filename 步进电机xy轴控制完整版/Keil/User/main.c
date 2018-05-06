/*
	本电机模块已经封装完毕，请勿擅自更改
	电机API简介：
		1. 初始化
		2. 设置X、Y轴电机转速
		3. 设置X、Y轴电机转向
		4. 启动X、Y轴电机
		5. 停止X、Y轴电机
		6. 命令X、Y轴电机运行一段时间
		7. 命令X、Y轴电机共同运行一段时间
*/
#include "reg51.h"
#include "sm.h"

#define uchar unsigned char

//定时2s，实际用了7s


/**
* MAIN
* 主程序实现X、Y电机同时运行，运行完毕后按原路返回
*/
void main(){

	sm_init();
	//sm_x_dir(SM_DIR_FORWARD);
	//sm_x_speed(600);
	//sm_x_start();

	//timer_init();
	//timer1_set_time(50000);
	//timer1_start();

	//sm_x_dir(SM_DIR_BACKWARD);
	//sm_x_speed(600);
	//sm_x_start();

	//sm_x_run(300, SM_DIR_FORWARD, 3000);
	//sm_x_run(300, SM_DIR_BACKWARD, 3000);

	while(1){

		sm_xy_run(500, SM_DIR_FORWARD, 300, SM_DIR_BACKWARD,2000);
		sm_xy_run(500, SM_DIR_BACKWARD, 300, SM_DIR_FORWARD, 2000);
		
		//sm_x_run(300, SM_DIR_FORWARD, 8000);
		//sm_x_run(300, SM_DIR_BACKWARD, 8000);	
	}
}
