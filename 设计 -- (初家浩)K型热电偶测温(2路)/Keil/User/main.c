#include "reg51.h"
#include "tck_max6675.h"
#include "lcd1602.h"
#include "timer.h"
#include "stdio.h"
#include "uart.h"

#define uchar unsigned char
#define uint unsigned int
#define DEBUG 0

void delay(uchar t);
char* get_str(int val);
void display();

//设置相关
sbit key_set = P0^5;
sbit key_up = P0^6;
sbit key_down = P0^7;
bit is_setting = 0;
bit is_read = 1;			//是否读取温度值
uchar set_road;				//当前设置报警温度的路

//参数
uint t1, t2;
uint t1max = 80, t2max = 75;

//报警相关
sbit buz = P3^6;

//锅炉升温/降温 反馈
sbit oven = P2^6;

//MAIN
void main(){
	uint temp1, temp2;
   	lcd_simple_init();
	uart_init();
	timer_init();
	

	//为防止第一次读到的误差，先读取一次温度
	tck_read_temp1();
	tck_read_temp2();

	while(1){

		//打印调试信息
		if(DEBUG){
			printf("--------------------DEBUG--------------------\n");
			printf("T1: %d \n", (int)t1);
			printf("T2: %d \n", (int)t2);
			printf("T1 Max: %d \n", (int)t1max);
			printf("T2 Max: %d \n", (int)t2max);
			printf("--------------------DEBUG--------------------\n\n");
			delay(100);
		}

		/***************** set/confirm set START ********************/
		//设置/应用设置
		if(!key_set){
			//当正在设置状态时，再次按下设置按钮，设置结束
			if(is_setting){
				is_setting = 0;
				is_read = 1;
				display();	
			}else{
				//进入设置模式，不读温度
				is_setting = 1;
				is_read = 0;
				//显示设置信息
				lcd_clear();
				lcd_display_string(1, 1, "SETTING..");
				if(set_road == 0){
					lcd_display_string(2, 1, "!T1 = ");
					lcd_display_string(2, 7, get_str(t1max));
				}else{
					lcd_display_string(2, 1, "!T2 = ");
					lcd_display_string(2, 7, get_str(t2max));
				}	
			}

			while(!key_set);		//等待按键松开
			if(!is_setting){
				set_road = !set_road;	//下次设置时，设置另一路	
			}			
		}
		/***************** set/confirm set END ********************/

	   	//增大/减小报警温度
		/***************** up/down START ********************/
		if(is_setting){
			if(!(!key_up && !key_down)){
				//增大报警温度
				if(!key_up){
					//可连续调整，必须消抖
					delay(255);
					if(!key_up){
						if(set_road == 0){
							t1max++;
							lcd_display_string(2, 1, "!T1 = ");
							lcd_display_string(2, 7, get_str(t1max));
						}else{
							t2max++;
							lcd_display_string(2, 1, "!T2 = ");
							lcd_display_string(2, 7, get_str(t2max));
						}
					}	
				}

				//减小报警温度
				if(!key_down){
					delay(255);
					if(!key_down){
						if(set_road == 0){
							t1max--;
							lcd_display_string(2, 1, "!T1 = ");
							lcd_display_string(2, 7, get_str(t1max));
						}else{
							t2max--;
							lcd_display_string(2, 1, "!T2 = ");
							lcd_display_string(2, 7, get_str(t2max));
						}
					}
				}
			}	
		}
		/***************** up/down END ********************/	


	   	/***************** read/display START ********************/
		if(is_read){
			temp1 = tck_read_temp1();		
			temp2 = tck_read_temp2();
		}

		//当温度值发生改变时，才重新显示
		if(temp1 != t1 || temp2 != t2){
			t1 = temp1;
			t2 = temp2;
			display();
		}
		/***************** read/display END ********************/

		/****************** warning START ******************/
		//两路温度，有一路超了则报警（忽略设置过程动态调节报警值）
		if(!is_setting){
			if(t1 > t1max || t2 > t2max){
				buz = 0;
				timer_stop();
				oven = 0;
			}else{
				buz = 1;
				timer_start();
			}	
		}	
		

		/****************** warning END ******************/

	}
			
}

//给oven脉冲
void timer_timeout(){
	oven = ~oven;
}

//显示1路温度、2路温度、1路报警值、2路报警值
void display(){
	char t1str[8], t2str[8], t1maxstr[8], t2maxstr[8];
	lcd_clear();

	//显示温度值
	sprintf(t1str, "T1: %d", (int)t1);
	sprintf(t2str, "T2: %d", (int)t2);
	lcd_display_string(1, 1, t1str);
	lcd_display_string(1, 9, t2str);
	
	//显示报警温度值
	sprintf(t1maxstr, "!T1: %d", (int)t1max);
	sprintf(t2maxstr, "!T2: %d", (int)t2max);
	lcd_display_string(2, 1, t1maxstr);
	lcd_display_string(2, 9, t2maxstr);
}

//将数字转换为字符串
char* get_str(int val){
	char *str;
	if(val <= 9){
		char arr[1];
		str = arr;
	}else if(val <= 99){
		char arr[2];
		str = arr;
	}else if(val <= 999){
		char arr[3];
		str = arr;
	}else if(val <= 9999){
		char arr[4];
		str = arr;
	}else if(val <= 99999){
		char arr[5];
		str = arr;
	}
	sprintf(str, "%d", val);
	return str;
}

//短暂延时
void delay(uchar t){
	uchar i, j;
	for(i=0;i<t;i++)
		for(j=0;j<110;j++);
}

//printf重定向
char putchar (char ch){
	uart_send(ch);
	return ch;
}


