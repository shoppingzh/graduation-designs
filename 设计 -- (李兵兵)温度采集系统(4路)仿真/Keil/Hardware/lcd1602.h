#ifndef _LCD1602_H_
#define _LCD1602_H_

#define uchar unsigned char
#define uint unsigned int
#define ENABLE 1
#define DISABLE 0

#define START_POSITION 0x80
#define POSITION_OFFSET 0x40
#define FIRST_LINE_VISIBLE_POSITION 0x80 + 0x0f														//��һ�����ɼ���ʾλ��
#define FIRST_LINE_MAX_POSITION START_POSITION + 0x27												//��һ�������ʾλ��
#define SECOND_LINE_START_POSITION START_POSITION + POSITION_OFFSET									//�ڶ�����ʼλ��
#define SECOND_LINE_VISIBLE_POSITION SECOND_LINE_START_POSITION + 0x0f								//�ڶ������ɼ���ʾλ��
#define SECOND_LINE_MAX_POSITION SECOND_LINE_START_POSITION SECOND_LINE_START_POSITION + 0x27 		//�ڶ��������ʾλ��

extern void lcd_init(uchar cursor_ena, uchar bling_ena);
extern void lcd_simple_init();
extern void lcd_clear();
extern void lcd_display_char(uchar line, uchar pos, char ch);
extern void lcd_display_string(uchar line, uchar pos, char* str);
//extern void lcd_display_digit(uchar line, uchar pos, uint d);
extern void lcd_write_com(uchar com);
extern void lcd_write_data(uchar value);

//LCD1602 �ɲ���ָ��
enum LCD1602_COM {
	DISPLAY_INIT = 0x38,				//��ʾ���ĳ�ʼ����16*2��ʾ��5*7����8λ���ݽӿ�
	DISPLAY_ON_CURSOR = 0x0e,			//��ʾģʽ������ʾ����ʾ��꣬��겻��˸
	DISPLAY_ON_NO_CURSOR = 0x0c,		//��ʾģʽ������ʾ������ʾ���
	DISPLAY_ON_CURSOR_BLING = 0x0f,		//��ʾģʽ������ʾ����ʾ����ҹ����˸
	DISPLAY_OFF = 0x80,					//��ʾģʽ���ر���ʾ
	WRITE_DIR_RIGHT = 0x06,				//��дģʽ����д����Ϊ�������ң�ָ���1������1
	WRITE_DIR_LEFT = 0x04,				//��дģʽ����д����Ϊ��������ָ���1������1
	WRITE_SCREEN_LEFT_MOVE = 0x07,		//��дģʽ��ÿдһ������Ļ����
	WRITE_SCREEN_RIGHT_MOVE = 0x05,		//��дģʽ��ÿдһ������Ļ����
	OPERATION_CLEAR = 0x01,				//����������������������ʾ������ָ�����㣩
	OPERATION_ENTER = 0x02,				//�����������س�����������ָ�����㣩			
};
	
#endif