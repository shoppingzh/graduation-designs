#ifndef _LCD1602_H_
#define _LCD1602_H_

#define uchar unsigned char
#define uint unsigned int
#define ENABLE 1
#define DISABLE 0

#define START_POSITION 0x80
#define POSITION_OFFSET 0x40
#define FIRST_LINE_VISIBLE_POSITION 0x80 + 0x0f														//第一行最大可见显示位置
#define FIRST_LINE_MAX_POSITION START_POSITION + 0x27												//第一行最大显示位置
#define SECOND_LINE_START_POSITION START_POSITION + POSITION_OFFSET									//第二行起始位置
#define SECOND_LINE_VISIBLE_POSITION SECOND_LINE_START_POSITION + 0x0f								//第二行最大可见显示位置
#define SECOND_LINE_MAX_POSITION SECOND_LINE_START_POSITION SECOND_LINE_START_POSITION + 0x27 		//第二行最大显示位置

extern void lcd_init(uchar cursor_ena, uchar bling_ena);
extern void lcd_simple_init();
extern void lcd_clear();
extern void lcd_display_char(uchar line, uchar pos, char ch);
extern void lcd_display_string(uchar line, uchar pos, char* str);
//extern void lcd_display_digit(uchar line, uchar pos, uint d);
extern void lcd_write_com(uchar com);
extern void lcd_write_data(uchar value);

//LCD1602 可操作指令
enum LCD1602_COM {
	DISPLAY_INIT = 0x38,				//显示器的初始化：16*2显示、5*7点阵、8位数据接口
	DISPLAY_ON_CURSOR = 0x0e,			//显示模式：开显示并显示光标，光标不闪烁
	DISPLAY_ON_NO_CURSOR = 0x0c,		//显示模式：开显示但不显示光标
	DISPLAY_ON_CURSOR_BLING = 0x0f,		//显示模式：开显示并显示光标且光标闪烁
	DISPLAY_OFF = 0x80,					//显示模式：关闭显示
	WRITE_DIR_RIGHT = 0x06,				//书写模式：书写方向为由左向右，指针加1并光标加1
	WRITE_DIR_LEFT = 0x04,				//书写模式：书写方向为由右向左，指针减1并光标减1
	WRITE_SCREEN_LEFT_MOVE = 0x07,		//书写模式：每写一个字屏幕左移
	WRITE_SCREEN_RIGHT_MOVE = 0x05,		//书写模式：每写一个字屏幕右移
	OPERATION_CLEAR = 0x01,				//其它操作：清屏操作（显示、数据指针清零）
	OPERATION_ENTER = 0x02,				//其它操作：回车操作（数据指针清零）			
};
	
#endif