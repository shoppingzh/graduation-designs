#include "lcd12864.h"
#include "reg51.h"
#define DB P1

sbit RS = P2^0;
sbit RW = P2^1;
sbit EN = P2^2;
sbit RST = P2^3;

/**
* �ڲ���ʱ����
*/
static void delay(uchar t){
	uchar i, j;
	for(i=0;i<t;i++){
		for(j=0;j<10;j++);
	}
}

/**
* LCD12864 �ȴ�æ�ź�
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
* LCD12864 ��ʼ������ͨģʽ
*/
void lcd_init(){
	RST = 0;				//��λ
	delay(1);
	RST = 1;
	
	lcd_write_com(0x30);	//ʹ��8λMPU�ӿ�
	delay(1);
	lcd_write_com(0x30);	//ʹ�û���ָ�
	delay(1);
	lcd_write_com(0x0c);	//����ʾ
	delay(1);
	lcd_write_com(0x01);	//����
	delay(1);
	lcd_write_com(0x06);	//�趨�α��ƶ�ģʽ	
}

/**
* LCD12864 дָ��
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
* LCD12864 д����
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
* LCD12864 �����ݣ���æ��
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
* LCD12864 ����Ļ�ϻ��Ƶ�
*/
void lcd_draw_point(uchar x, uchar y){
	uint bt, dat;
	uchar x_adr, y_adr, high, low;		//X��Y��ַ��д��ĸߵ��ֽ�
	lcd_write_com(0x34);
	lcd_write_com(0x34);

	//ȷ����ʾλ��
	y_adr = 0x80 + y % 32;
	if(y > 31)
		x_adr = 0x88 + x / 16;
	else
		x_adr = 0x80 + x / 16;

	//��ȡ��ǰ�����Ϣ
	bt = 0x8000 >> (x % 16);
	lcd_write_com(y_adr);	//д���ȡλ�ã���ȡ����������
	lcd_write_com(x_adr);
	lcd_read_data();		//������һ���ֽ�
	dat = lcd_read_data();
	dat <<= 8;
	dat |= lcd_read_data();
	bt |= dat;				//��Ҫ��ʾ�ĵ������ǰ�ĵ�
	high = bt >> 8;
	low = bt;

	//д���µ���Ϣ
	lcd_write_com(y_adr);	
	lcd_write_com(x_adr);
   	lcd_write_data(high);
	lcd_write_data(low);

	lcd_write_com(0x36);
	lcd_write_com(0x30);
}

/**
* LCD12864 �����ͼ����
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
* LCD12864 ��ָ����λ����д����
* @param x		�����ַ�������ʾ�У���ֵ���ܴ���4
* @param y		�����ַ�������ʾ�У���ֵ���ܴ���8
* @param str	�����ַ���
*/
void lcd_display_string(uchar row, uchar col, char* str){
	uchar adr;
	if(row < 1 || col < 1 || row > 4 || col > 8)
		return;
	if(row == 1){
		adr = 0x80 + col - 1;	
	}else if(row == 2){
		adr = 0x90 + col - 1;
	}else if(row == 3){
		adr = 0x88 + col - 1;
	}else if(row == 4){
		adr = 0x98 + col - 1;
	}

	lcd_write_com(adr);
	while(*str){
		lcd_write_data(*str);
		str++;
	}
}
