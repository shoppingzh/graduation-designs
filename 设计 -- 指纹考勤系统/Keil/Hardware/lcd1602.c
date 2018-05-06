#include "lcd1602.h"
#include "reg51.h"
#define OUT P0

sbit RS = P2^6;
sbit RW = P2^5;
sbit EN = P2^7;

/**
* �ڲ���ʱ����
*/
static void delay(uchar t){
	uchar i, j;
	for(i=0;i<t;i++){
		for(j=0;j<50;j++);
	}
}

/**
* LCD1602 ��æ
*/
static void check_busy(){
	uchar t;
	RS = 0;		//��������
	RW = 1;		//������
	EN = 0;
	while(1){
		OUT = 0xff;
		EN = 1;
		t = OUT;
		EN = 0;
		//������λBF�Ƿ�Ϊ0����0��Ϊ��æ״̬
		if(!(t & 0x80))
			break;
	}
}

/**
* LCD1602 ��ʼ��
* ��ʼ���������²�����
*		1. ��ʾ���ĳ�ʼ��
*		2. ��ʾģʽ���ã��Ƿ��й�ꡢ����Ƿ���˸��
*		3. ��дģʽ���ã��������ҡ�����������Ļ�ƶ���
*		4. ����
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
* LCD1602 �򵥳�ʼ��������ʾ��꣬��д������������
*/
void lcd_simple_init(){
	lcd_init(DISABLE, DISABLE);	
}

/**
* LCD1602 ����
*/
void lcd_clear(){
	lcd_write_com(OPERATION_CLEAR);	
}

/**
* LCD1602 ����Ļ����ʾһ���ַ�
* @param line ��ʾ�����������ɴ���2��
* @param pos  ��ʾ��λ�ã����ɴ���16��
* @param ch	  ��Ҫ��ʾ���ַ�
*/
void lcd_display_char(uchar line, uchar pos, char ch){
	if(line == 0 || line > 2 || pos == 0 || pos > 16)
		return;
	lcd_write_com(START_POSITION + (line - 1) * POSITION_OFFSET + pos - 1);
	lcd_write_data(ch);	
}

/**
* LCD1602 ����Ļ����ʾ�ַ���
* @param line ��ʾ�����������ɴ���2��
* @param pos  ��ʾ��λ�ã����ɴ���16��
* @param str  ��Ҫ��ʾ���ַ���
*/
void lcd_display_string(uchar line, uchar pos, char* str){
	while(*str){
		lcd_display_char(line, pos++, *str);
		str++;
	}	
}

/**
* LCD1602 д��ָ��
*/
void lcd_write_com(uchar com){
	check_busy();
	EN = 0;
	RS = 0;			//����ָ��
	delay(1);
	RW = 0;			//д����
	delay(1);
	OUT = com;		//д��ָ��
	delay(1);	
	EN = 1;	 		//���������
	delay(1);
	EN = 0;
}

/**
* LCD1602 д������
*/
void lcd_write_data(uchar value){
	check_busy();
	EN = 0;
	RS = 1;			//��������
	delay(1);
	RW = 0;			//д����
	delay(1);
	OUT = value;	//д������
	delay(1);	
	EN = 1;	 		//���������
	delay(1);
	EN = 0;
}