#include "reg52.h"
#include "lcd12864.h"
#include "intrins.h"
#include "adc.h"

#define trigger(d) (d < 127)	//是否触发（触发条件为挡住）
#define DEBUG 0					//调试模式
#define MAX_VALID_PEOPLE 50		//最大限载人数

void delay(uint t);
void collect();
void analyse();
void check();

void home_page();
void setting_page();
void set_success_page();

sbit AD_CHANNEL = P3^3;			//AD通道
sbit relay = P3^0;				//继电器
sbit buzzer = P3^1;				//蜂鸣器
sbit key_set = P3^5;			//设置键
sbit key_up = P3^6;				//加键
sbit key_down = P3^7;			//减键

volatile uchar o1, o2; 			//两个通道采集到的值
int people = 0;	  				//车上人数
uchar flag_in, flag_out; 		//进出过程标志
bit inout = 0;		   			//进出标志位
int overload_people = 10;   	//限载人数
bit setting = 0; 				//设置状态标志位

/**
* 主页
*/
void home_page(){
	lcd_display_string(1, 2, "实时监控信息");

	lcd_display_string(2, 1, "车内乘客：");
	lcd_display_digit(2, 6, people);
	lcd_display_string(2, 7, "人");

	lcd_display_string(3, 1, "限载乘客：");
	lcd_display_digit(3, 6, overload_people);
	lcd_display_string(3, 7, "人");
}

/**
* 设置页面
*/
void setting_page(){
	lcd_clear();
	lcd_display_string(1, 1, "当前限载乘客：");
	lcd_display_digit(1, 8, overload_people);
	lcd_display_string(3, 1, "按下上、下键增大");
	lcd_display_string(4, 1, "或减少限载乘客");
}

/**
* 设置成功界面
*/
void set_success_page(){
	lcd_clear();
	lcd_display_string(2, 3, "设置成功！");
}

/////////////////////////////////////////////MAIN
void main(){

	lcd_init();
	adc_init();
   	home_page();

	while(1){
	
		//按键检测
		if(!key_set){
			setting = ~setting;
			if(setting){
				setting_page();
			}else{
				set_success_page();	
				delay(1000);
				home_page();
			}
			while(!key_set);	
		}

		if(setting){
		 	if(!(!key_up && !key_down)){
				if(!key_up){
					delay(50);
					if(!key_up){
						if(overload_people < MAX_VALID_PEOPLE){
							overload_people++;
							setting_page();
						}		
					}
				}
				if(!key_down){
					delay(50);
					if(!key_down){
						if(overload_people > 1){
							overload_people--;
							setting_page();
						}		
					}
				}
			}	
		}else{
			collect();
			analyse();
			check();

			if(DEBUG){
				lcd_clear_line(2);
				lcd_clear_line(3);
	
				lcd_display_string(2, 1, "模拟量一：");
				lcd_display_digit(2, 6, (int)o1);
				lcd_display_string(3, 1, "模拟量二：");
				lcd_display_digit(3, 6, (int)o2);
			}
		}		
	}


}

/**
* 普通延时（ms）
*/
void delay(uint t){
    uint a,b;
    for(a=0;a<t;a++)
		for(b=0;b<110;b++);
}

/**
* 采集两路数字量
*/
void collect(){
	uchar i;

	AD_CHANNEL = 0;
	delay(5);
	for(i=0;i<10;i++){
		o1 = adc_transform();
	}

	AD_CHANNEL = 1;
	delay(5);
	for(i=0;i<10;i++){
		o2 = adc_transform();	
	}	
}

/**
* 打印调试信息
*/
static void debug_msg(char *str){
	lcd_clear_line(4);
	lcd_display_string(4, 1, str);
}

/**
* 根据传感器的触发顺序分析上下车情况
*/
void analyse(){
	bit update = 0;
	if(o1 == 0 && o2 == 0)
		return;

	//传感器1的触发
	if(trigger(o1)){
		if(flag_in == 0 && flag_out == 0){
			inout = 0;
		}
		if(inout == 0){
			//从外面到触碰第一个传感器，开始进门
			if(flag_in == 0){
				flag_in = 1;
				if(DEBUG){
					debug_msg("开始进门");
				}	
			}
		}else{
			//从中间触碰到第一个传感器，即将出门
			if(flag_out == 2){
				flag_out = 3;
				if(DEBUG){
					debug_msg("即将出门");
				}
			}
		}					
	}else{
		if(inout == 0){
			//穿过第一个传感器，进到两个传感器中间
			if(flag_in == 1){
				flag_in = 2;
				if(DEBUG){
					debug_msg("位于中间位置");
				}
			} 
		}else{
			//离开第一个传感器，走出门外，人数减1
			if(flag_out == 3){
				flag_out = 0;
				if(people > 0){
					people--;
					update = 1;
					if(DEBUG){
						debug_msg("走出门外");
					}
				}	
			}	
		}	
	}

	//传感器2的触发
	if(trigger(o2)){
		if(flag_in == 0 && flag_out == 0){
			inout = 1;			
		}
		if(inout == 0){
			//从中间触碰到第二个传感器，即将进门
			if(flag_in == 2){
				flag_in = 3;
				if(DEBUG){
					debug_msg("即将进门");
				}
			}
		}else{
			//从里面触碰到第二个传感器，开始出门
		   	if(flag_out == 0){
				flag_out = 1;
				if(DEBUG){
					debug_msg("开始出门");
				}
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
					if(DEBUG){
						debug_msg("进入门内");
					}
				}	
			}
		}else{
			//离开第二个传感器，出到两个传感器中间
			if(flag_out == 1){
				flag_out = 2;
				if(DEBUG){
					debug_msg("位于中间位置");
				}
			}	
		}	
	}


	//根据需要显示人数信息
	if(update){
		home_page();	
	}
}

/**
* 报警
*/
static void warning(){
	buzzer = ~buzzer;
	delay(1);
	buzzer = ~buzzer;
	delay(1);
}

/**
* 检查是否超载
*/
void check(){
	if(people > overload_people){
		warning();
		relay = 0;			
	}else{
		relay = 1;
	}	
}