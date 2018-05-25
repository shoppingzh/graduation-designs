#include "reg52.h"
#include "lcd1602.h"
#include "adc.h"
#include "stdio.h"
#include "intrins.h"

#define DEFAULT_OVER_WEIGHT 80
#define get_w(v) ((115 - 15) * 1.0f / (243 - 13) * v + 10)

uchar get(uchar channel);
uchar avg();

sbit ADDA = P3^2;
sbit ADDB = P3^3;
sbit ADDC = P3^4;
sbit key_set = P3^5;
sbit key_up = P3^6;
sbit key_down = P3^7;
sbit ctrl = P3^0;
sbit warning = P3^1;

uchar weight;
bit setting = 0;
uchar over_weight = DEFAULT_OVER_WEIGHT;

//选择模拟通道
static void choose(uchar channel){
	switch(channel){
		case 0:
			ADDA = 0;ADDB = 0;ADDC = 0;
			break;
		case 1:
			ADDA = 1;ADDB = 0;ADDC = 0;
			break;
		case 2:
			ADDA = 0;ADDB = 1;ADDC = 0;
			break;
		case 3:
			ADDA = 1;ADDB = 1;ADDC = 0;
			break;
		case 4:	 
			ADDA = 0;ADDB = 0;ADDC = 1;
			break;
		default:
			ADDA = 0;ADDB = 0;ADDC = 0;
			break;
	}
}

//普通延时
static void delay(uint t){
	uint i, j;
	for(i=0;i<t;i++){
		for(j=0;j<110;j++);
	}
}

//设置界面
static void setting_page(){
	uchar str[16];
	lcd_display_string(1, 1, "Set max weight: ");
	sprintf(str, "%16d", (int)over_weight);
	lcd_display_string(2, 1, str);		

}

//工作界面 force: 是否强制显示
static void working_page(uchar force){
	uchar str[16], curr;
	curr = avg();		
	if(curr != weight || force){
		lcd_clear();

		//显示当前重量
		weight = curr;
		sprintf(str, "Weight: %d", (int)weight);
		lcd_display_string(1, 1, str);

		//显示超重信息
		if(weight > over_weight){
			lcd_display_string(2, 1, "Overweight: Yes");
		}else{
			lcd_display_string(2, 1, "Overweight: No");
		}
	}
}


void main(){
	lcd_simple_init();
	ctrl = 0;

	while(1){

		if(!key_set){
			if(setting){
				//确认设置
				lcd_clear();
				setting = 0;
				working_page(1);
			}else{
				//进入设置
				lcd_clear();
				setting = 1;
				setting_page();
			}

			while(!key_set);
		}
		
		if(setting){
			if(!key_up){
				delay(100);
				if(!key_up){
					if(over_weight < 115){
						over_weight++;
						setting_page();
					}		
				}
			}
			if(!key_down){
				delay(100);
				if(!key_down){
					if(over_weight > 0){
						over_weight--;
						setting_page();
					}	
				}
			}			
		}else{
			working_page(0);
			if(weight > over_weight){
				warning = 0;
				ctrl = 1;	
			}else{
				warning = 1;
				ctrl = 0;
			}	
		}
	}
}

/**
* 获取某路的重量
*/
uchar get(uchar channel){
	uchar i;
	choose(channel);
	delay(5);
	for(i=0;i<10;i++){
		adc_transform();
	}	

	return get_w(adc_transform());
}

/**
* 获取5路重量值的平均值
*/
uchar avg(){
	uchar w0, w1, w2, w3, w4;
	uint sum;
	w0 = get(0);
	w1 = get(1);
	w2 = get(2);
	w3 = get(3);
	w4 = get(4);
	sum = w0 + w1 + w2 + w3 + w4;

	return sum / 5;
}

