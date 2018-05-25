#include "reg51.h"
#include "adc.h"
#include "uart.h"
#include "lcd1602.h"
#include "stdio.h"

void delay(uchar);
void display_vol(uchar, uchar);
void display();

sbit ADDA = P2^4;
sbit ADDB = P2^5;
sbit ADDC = P2^6;

uchar rode;
uchar vol;
bit state = 0;				//接收上位机标志位
bit changed = 0;			//温度值是否变化

/////////MAIN
void main(){
	uchar temp;
	uart_init();
	lcd_simple_init();
	lcd_display_string(1, 1, "Waiting..");
	
	while(1){
		//上位机才能改变该状态位，该位为1时，开始转换并显示
		if(state){
			temp = adc_transform();
			if(temp != vol){
				vol = temp;
				display();
			}
			uart_send(vol);
			state = 0;
		}		
	}

}

//串口接收回调：接收上位机指令，选择开启的模拟通道（对应不同量程的电压测量）
void uart_received(uchar cmd){
	state = 1;
	if(cmd == 0x01){
		ADDA = 0;
		ADDB = 0;
		ADDC = 0;
		rode = 1;
	}else if(cmd == 0x02){
		ADDA = 1;
		ADDB = 0;
		ADDC = 0;
		rode = 2;	
	}else if(cmd == 0x03){
		ADDA = 0;
		ADDB = 1;
		ADDC = 0;
		rode = 3;
	}else if(cmd == 0x04){
		ADDA = 1;
		ADDB = 1;
		ADDC = 0;
		rode = 4;
	}	
}

//延时
void delay(uchar t){
	uchar i, j, k;
	for(i=0;i<t;i++)
		for(j=0;j<20;j++)
			for(k=0;k<110;k++);
}

//显示对应电压
void display_vol(uchar row, uchar col){
	char str[10];
	int v = vol;
	float range;
	//对应量程显示不同的电压值
	if(rode == 1){
		range = 0.5f;	
	}else if(rode == 2){
		range = 5.0f;		
	}else if(rode == 3){
		range = 50.0f;		
	}else if(rode == 4){
		range = 500.0f;		
	}
	sprintf(str, "%.2fV", (v / 255.0 * range));		
	lcd_display_string(row, col, str);	
}

//显示
void display(){
	char* str;
	lcd_clear();
	lcd_display_string(1, 1, "Range: ");
	if(rode == 1){
		str = "(0-0.5V)";
	}else if(rode == 2){
		str = "(0-5V)";
	}else if(rode == 3){
		str = "(0-50V)";
	}else if(rode == 4){
		str = "(0-500V)";
	}else{
		str = "";
	}
	lcd_display_string(1, 8, str);
	lcd_display_string(2, 1, "VOL: ");
	display_vol(2, 6);
}
