#include "reg51.h"
#include "intrins.h"
#include "uart.h"
#include "temper.h"
#include "lcd1602.h"
#include "stdio.h"

#define uchar unsigned char
#define uint unsigned int

#define MODE_WORK 0x10				//工作模式
#define MODE_SETTINGS 0x11			//设置模式

void delay(uchar t);
void display();
void read_temps();

sbit warning = P3^7;

uchar t1, t2, t3, t4;
uchar road;
bit update;
uchar mode = MODE_WORK;
uchar max_temp = 255;

/////////MAIN
void main(){
	uart_init();
	lcd_simple_init();

	while(1){
		if(mode == MODE_WORK){
			read_temps();
			if(update){
				display();
				update = 0;
			}
			if(t1 > max_temp || t2 > max_temp ||
				t3 > max_temp || t4 > max_temp){
				warning = 0;	
			}else{
				warning = 1;
			}
		}	
	}
}

//读取温度并显示
void read_temps(){
	uchar temp;
	temp = temper_readtemp1();
	if(temp != t1){
		t1 = temp;
		update = 1;
	}
	delay(10);
		
	temp = temper_readtemp2();
	if(temp != t2){
		t2 = temp;
		update = 1;	
	}
	delay(10);

	temp = temper_readtemp3();
	if(temp != t3){
		t3 = temp;
		update = 1;	
	}
	delay(10);

	temp = temper_readtemp4();
	if(temp != t4){
		t4 = temp;
		update = 1;	
	}
}

void delay3s(void)   //误差 0us
{
    unsigned char a,b,c;
    for(c=189;c>0;c--)
        for(b=230;b>0;b--)
            for(a=33;a>0;a--);
}

//串口接收回调
void uart_received(uchar cmd){
	//设置优先
	if(mode == MODE_SETTINGS){
		char str[3];
		max_temp = cmd;
		sprintf(str, "%d", (int)max_temp);
		lcd_display_string(2, 1, "Warning: ");
		lcd_display_string(2, 10, str);

		//等待3s切回工作模式
		delay3s();
		update = 1;
		mode = MODE_WORK;
		return;	
	}

	if(cmd == 1){
		mode = MODE_WORK;
		uart_send(t1);
	}else if(cmd == 2){
		mode = MODE_WORK;
	   	uart_send(t2);
	}else if(cmd == 3){
		mode = MODE_WORK;
		uart_send(t3);
	}else if(cmd == 4){
		mode = MODE_WORK;
		uart_send(t4);
	}else if(cmd == 0x10){
		mode = MODE_SETTINGS;
		lcd_clear();
		lcd_display_string(1, 1, "Setting..");
	}	
}

//延时
void delay(uchar t){
	int i, j;
	for(i=0;i<t;i++)
		for(j=0;j<110;j++);
}

//显示
void display(){
	char arr1[5], arr2[5], arr3[5], arr4[5];
	lcd_clear();
   	lcd_display_string(1, 1, "T1: ");
	lcd_display_string(1, 8, "T2: ");
	lcd_display_string(2, 1, "T3: ");
	lcd_display_string(2, 8, "T4: ");

	sprintf(arr1, "%d", (int)t1);
	sprintf(arr2, "%d", (int)t2);
	sprintf(arr3, "%d", (int)t3);
	sprintf(arr4, "%d", (int)t4);
	lcd_display_string(1, 4, arr1);
	lcd_display_string(1, 11, arr2);
	lcd_display_string(2, 4, arr3);
	lcd_display_string(2, 11, arr4);
}
