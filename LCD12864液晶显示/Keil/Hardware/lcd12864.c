#include "lcd12864.h"
#include "reg51.h"
#define DB P1

sbit RS = P2^0;
sbit RW = P2^1;
sbit EN = P2^2;
sbit RST = P2^3;
sbit PSB = P2^4;

/**
* 内部延时程序
*/
static void delay(uchar t){
	uchar i, j;
	for(i=0;i<t;i++){
		for(j=0;j<10;j++);
	}
}

/**
* LCD12864 等待忙信号
*/
static void wait_busy(){
	uchar t;
	DB = 0xff;
	RS = 0;
	RW = 1;
	EN = 1;
	for(t=0;t<10;t++){
		if(!(DB & 0x80))
			break;
	}
	EN = 0;
}

/**
* 获取所在位置的地址
* @param row	行索引，从1开始
* @param col	列索引，从1开始
*/
static uchar get_addr(uchar row, uchar col){
	uchar adr = 0x80;
	if(row == 1){
		adr = 0x80 + col - 1;	
	}else if(row == 2){
		adr = 0x90 + col - 1;
	}else if(row == 3){
		adr = 0x88 + col - 1;
	}else if(row == 4){
		adr = 0x98 + col - 1;
	}
	return adr;
}

/**
* LCD12864 初始化，普通模式
*/
void lcd_init(){
	RST = 0;				//复位
	delay(100);
	RST = 1;
	PSB = 1;
	delay(100);

	lcd_write_com(0x30);	//使用8位MPU接口
	delay(1);
	lcd_write_com(0x30);	//使用基本指令集
	delay(1);
	lcd_write_com(0x0c);	//打开显示
	delay(1);
	lcd_write_com(0x01);	//清屏
	delay(1);
	lcd_write_com(0x06);	//设定游标移动模式	
}

/**
* LCD12864 写指令
*/
void lcd_write_com(uchar com){
	RS = 0;
	RW = 0;
	EN = 0;
	delay(1);
	DB = com;
	EN = 1;
	delay(1);
	EN = 0;
}

/**
* LCD12864 写数据
*/
void lcd_write_data(uchar dat){
	RS = 1;
	RW = 0;
	EN = 0;
	delay(1);
	DB = dat;
	EN = 1;
	delay(1);
	EN = 0;
}

/**
* LCD12864 读数据（测忙）
*/
uchar lcd_read_data(){
	uchar dat;
	wait_busy();
	RS = 1;
	RW = 1;
	EN = 0;
	delay(1);
	EN = 1;
	delay(1);
	dat = DB;
	EN = 0;
	delay(1);
	return dat;
}

/**
* LCD12864 在屏幕上绘制点
*/
void lcd_draw_point(uchar x, uchar y){
	uint bt, dat;
	uchar x_adr, y_adr, high, low;		//X、Y地址，写入的高低字节
	lcd_write_com(0x34);
	lcd_write_com(0x34);

	//确定显示位置
	y_adr = 0x80 + y % 32;
	if(y > 31)
		x_adr = 0x88 + x / 16;
	else
		x_adr = 0x80 + x / 16;

	//读取以前点的信息
	bt = 0x8000 >> (x % 16);
	lcd_write_com(y_adr);	//写入读取位置，读取这个点的数据
	lcd_write_com(x_adr);
	lcd_read_data();		//舍弃第一个字节
	dat = lcd_read_data();
	dat <<= 8;
	dat |= lcd_read_data();
	bt |= dat;				//将要显示的点或上以前的点
	high = bt >> 8;
	low = bt;

	//写入新的信息
	lcd_write_com(y_adr);	
	lcd_write_com(x_adr);
   	lcd_write_data(high);
	lcd_write_data(low);

	lcd_write_com(0x36);
	lcd_write_com(0x30);
}

/**
* LCD12864 清除画图内容
*/
void lcd_graphics_clear(){
 	uchar i, j;
	lcd_write_com(0x34);
	lcd_write_com(0x34);

	for(i=0;i<32;i++){
		lcd_write_com(0x80 + i);
		lcd_write_com(0x80);
		for(j=0;j<32;j++){
			lcd_write_data(0x00);
		}
	}

	lcd_write_com(0x36);
	lcd_write_com(0x30);
}

/**
* LCD12864 在指定位置书写ASCII码
* @param row	显示行
* @param col	显示列
* @param left 	左ASCII码字符
* @param right	右ASCII码字符
*/
void lcd_display_ascii(uchar row, uchar col, char left, char right){
	lcd_write_com(0x30);		
	lcd_write_com(get_addr(row, col));

	lcd_write_data(left == 0 ? ' ' : left);
	lcd_write_data(right == 0 ? ' ' : right);
}

/**
* LCD12864 在指定的位置书写中文
* @param row	中文字符串的显示行，该值不能大于4
* @param col	中文字符串的显示列，该值不能大于8
* @param str	中文字符串
*/
void lcd_display_string(uchar row, uchar col, char* str){
	uchar adr;
	if(row < 1 || col < 1 || row > 4 || col > 8)
		return;
	adr = get_addr(row, col);

	lcd_write_com(adr);
	while(*str){
		lcd_write_data(*str);
		str++;
	}
}

/**
* 显示数字，最多显示5位
*/
void lcd_display_digit(uchar row, uchar col, uint d){
	uchar addr = get_addr(row, col);
	lcd_write_com(0x30);
	lcd_write_com(addr);						
	if(d <= 9){
		lcd_write_data(' ');
		lcd_write_data(d + 48);
	}else if(d <= 99){
		lcd_write_data(d / 10 + 48);
		lcd_write_data(d % 10 + 48);
	}else if(d <= 999){
		lcd_write_data(' ');
		lcd_write_data(d / 100 + 48);
		lcd_write_com(addr + 1);
		lcd_write_data(d / 10 % 10 + 48);
		lcd_write_data(d % 10 + 48);
	}else if(d <= 9999){
		lcd_write_data(d / 1000 + 48);
		lcd_write_data(d / 100 % 10 + 48);
		lcd_write_com(addr + 1);
		lcd_write_data(d / 10 % 10 + 48);
		lcd_write_data(d % 10 + 48);
	}else if(d <= 99999){
		lcd_write_data(' ');
		lcd_write_data(d / 10000 + 48);
		lcd_write_com(addr + 1);
		lcd_write_data(d / 1000 % 10 + 48);
		lcd_write_data(d / 100 % 10 + 48);
		lcd_write_com(addr + 2);
		lcd_write_data(d / 10 % 10 + 48);
		lcd_write_data(d % 10 + 48);
	}
}

/**
* 清屏
*/
void lcd_clear(){
	lcd_write_com(0x01);
	delay(50);
}
