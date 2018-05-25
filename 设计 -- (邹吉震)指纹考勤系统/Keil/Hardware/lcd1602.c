#include "lcd1602.h"
#include "reg51.h"
#define OUT P0

sbit RS = P2^6;
sbit RW = P2^5;
sbit EN = P2^7;

/**
* 内部延时程序
*/
static void delay(uchar t){
	uchar i, j;
	for(i=0;i<t;i++){
		for(j=0;j<50;j++);
	}
}

/**
* LCD1602 测忙
*/
static void check_busy(){
	uchar t;
	RS = 0;		//操作命令
	RW = 1;		//读操作
	EN = 0;
	while(1){
		OUT = 0xff;
		EN = 1;
		t = OUT;
		EN = 0;
		//检查最高位BF是否为0，是0则为不忙状态
		if(!(t & 0x80))
			break;
	}
}

/**
* LCD1602 初始化
* 初始化包含以下操作：
*		1. 显示器的初始化
*		2. 显示模式设置（是否有光标、光标是否闪烁）
*		3. 书写模式设置（由左向右、由右向左、屏幕移动）
*		4. 清屏
*/
void lcd_init(uchar cursor_ena, uchar bling_ena){
	lcd_write_com(DISPLAY_INIT);

	if(cursor_ena == ENABLE){
		lcd_write_com(DISPLAY_ON_CURSOR);
		if(bling_ena == ENABLE){
		 	lcd_write_com(DISPLAY_ON_CURSOR_BLING);	
		}	
	}else{
		lcd_write_com(DISPLAY_ON_NO_CURSOR);
	}

	lcd_write_com(WRITE_DIR_RIGHT);

	lcd_clear();	
}

/**
* LCD1602 简单初始化：不显示光标，书写方向由左向右
*/
void lcd_simple_init(){
	lcd_init(DISABLE, DISABLE);	
}

/**
* LCD1602 清屏
*/
void lcd_clear(){
	lcd_write_com(OPERATION_CLEAR);	
}

/**
* LCD1602 在屏幕上显示一个字符
* @param line 显示的行数（不可大于2）
* @param pos  显示的位置（不可大于16）
* @param ch	  需要显示的字符
*/
void lcd_display_char(uchar line, uchar pos, char ch){
	if(line == 0 || line > 2 || pos == 0 || pos > 16)
		return;
	lcd_write_com(START_POSITION + (line - 1) * POSITION_OFFSET + pos - 1);
	lcd_write_data(ch);	
}

/**
* LCD1602 在屏幕上显示字符串
* @param line 显示的行数（不可大于2）
* @param pos  显示的位置（不可大于16）
* @param str  需要显示的字符串
*/
void lcd_display_string(uchar line, uchar pos, char* str){
	while(*str){
		lcd_display_char(line, pos++, *str);
		str++;
	}	
}

/**
* LCD1602 写入指令
*/
void lcd_write_com(uchar com){
	check_busy();
	EN = 0;
	RS = 0;			//操作指令
	delay(1);
	RW = 0;			//写操作
	delay(1);
	OUT = com;		//写入指令
	delay(1);	
	EN = 1;	 		//获得上升沿
	delay(1);
	EN = 0;
}

/**
* LCD1602 写入数据
*/
void lcd_write_data(uchar value){
	check_busy();
	EN = 0;
	RS = 1;			//操作数据
	delay(1);
	RW = 0;			//写操作
	delay(1);
	OUT = value;	//写入数据
	delay(1);	
	EN = 1;	 		//获得上升沿
	delay(1);
	EN = 0;
}