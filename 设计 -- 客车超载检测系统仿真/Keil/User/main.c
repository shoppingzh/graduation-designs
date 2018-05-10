#include "reg51.h"
#include "adc.h"
#include "lcd1602.h"
#include "stdio.h"
#include "intrins.h"

#define MAX_DISTANCE 40
#define MAX_VALID_PEOPLE 50
#define cal(ad) ((1.0f / (ad * 0.0005f + 0.00158f)) - 7)		//AD --> 距离转换公式
#define trigger(distance) (distance < MAX_DISTANCE)

void delay(uint t);
void get_distance();
void analyse();
void display_inside();
void display_max();

sbit ADDA = P2^7;
sbit key_set = P3^0;
sbit key_up = P3^1;
sbit key_down = P3^2;
sbit warning = P3^3;
sbit control = P3^4;

float d1, d2;					//d1/d2：第一（二）个传感器采集到的距离
int people = 0;					//车上人数
uchar flag_in, flag_out;		//进出过程标志
bit inout = 0;					//进或出的标志位（为0时为进，为1时为出）
int max_people = 0;				//限载人数
bit setting = 1;				//是否处于设置状态


void main(){
	lcd_simple_init();
	lcd_display_string(1, 1, "Init Setting: ");
	ADDA = 0;
	control = 0;

	while(1){

		//进入/退出设置
		if(!key_set){
			setting = ~setting;
			if(setting){
				char str[16];
				sprintf(str, "Max Overload:%d", max_people);
				lcd_clear();
				lcd_display_string(1, 1, "Setting..");
				lcd_display_string(2, 1, str);

			}else{
				display_inside();
			}
			while(!key_set);	
		}

		//增加/减少最大限载人数
		if(setting){
			if(!(!key_up && !key_down)){
				if(!key_up){
					delay(100);
					if(!key_up){
						if(max_people < MAX_VALID_PEOPLE){
							max_people++;
							display_max();
						}		
					}
				}
				if(!key_down){
					delay(100);
					if(!key_down){
						if(max_people > 1){
							max_people--;
							display_max();
						}		
					}
				}
			}		
		}else{
			//运行状态
		   	get_distance();
			analyse();
			if(people > max_people){
				warning = 0;
				control = 1;			
			}else{
				warning = 1;
				control = 0;
			}
		}
	}
}

void display_max(){
	uchar str[16];
	lcd_display_string(1, 1, "Max Overload: ");
	sprintf(str, "%16d", max_people);
	lcd_display_string(2, 1, str);
}

/**
* 传感器采集切换延时
*/
void delay(uint t){
    uint a,b;
    for(a=0;a<t;a++)
		for(b=0;b<110;b++);
}

/**
* 获取两个传感器采集到的距离
*/
void get_distance(){
	uchar i;
	ADDA = 0;
	delay(1);
	for(i=0;i<3;i++){
	   d1 = cal(adc_transform());
	}

	ADDA = 1;
   	delay(1);
	for(i=0;i<3;i++){
	   d2 = cal(adc_transform());
	}
}

/**
* 显示当前车上人数
*/
void display_inside(){
	uchar str[16];
	sprintf(str, "Inside: %d", (int)people);
	lcd_clear();
	lcd_display_string(1, 1, str);
}

/**
* 根据传感器的触发顺序分析上下车情况
*/
void analyse(){
	bit update = 0;
	if(d1 == 0 || d2 == 0)
		return;

	//传感器1的触发
	if(trigger(d1)){
		if(flag_in == 0 && flag_out == 0){
			inout = 0;
		}
		if(inout == 0){
			//从外面到触碰第一个传感器，开始进门
			if(flag_in == 0){
				flag_in = 1;	
			}
		}else{
			//从中间触碰到第一个传感器，即将出门
			if(flag_out == 2){
				flag_out = 3;
			}
		}					
	}else{
		if(inout == 0){
			//穿过第一个传感器，进到两个传感器中间
			if(flag_in == 1){
				flag_in = 2;
			} 
		}else{
			//离开第一个传感器，走出门外，人数减1
			if(flag_out == 3){
				flag_out = 0;
				if(people > 0){
					people--;
					update = 1;
				}	
			}	
		}	
	}

	//传感器2的触发
	if(trigger(d2)){
		if(flag_in == 0 && flag_out == 0){
			inout = 1;			
		}
		if(inout == 0){
			//从中间触碰到第二个传感器，即将进门
			if(flag_in == 2){
				flag_in = 3;
			}
		}else{
			//从里面触碰到第二个传感器，开始出门
		   	if(flag_out == 0){
				flag_out = 1;
			}
		}						
	}else{
		if(inout == 0){
			//离开第二个传感器，进入门内，人数加1
		 	if(flag_in == 3){
				flag_in = 0;
				if(people < 255){
					people++;
					update = 1;
				}	
			}
		}else{
			//离开第二个传感器，出到两个传感器中间
			if(flag_out == 1){
				flag_out = 2;
			}	
		}	
	}


	//根据需要显示人数信息
	if(update){
		display_inside();	
	}
}
