#include "reg51.h"
#include "tck_max6675.h"
#include "lcd1602.h"
#include "timer.h"
#include "stdio.h"
#include "uart.h"

#define uchar unsigned char
#define uint unsigned int
#define DEBUG 0

void delay(uchar t);
char* get_str(int val);
void display();

//�������
sbit key_set = P0^5;
sbit key_up = P0^6;
sbit key_down = P0^7;
bit is_setting = 0;
bit is_read = 1;			//�Ƿ��ȡ�¶�ֵ
uchar set_road;				//��ǰ���ñ����¶ȵ�·

//����
uint t1, t2;
uint t1max = 80, t2max = 75;

//�������
sbit buz = P3^6;

//��¯����/���� ����
sbit oven = P2^6;

//MAIN
void main(){
	uint temp1, temp2;
   	lcd_simple_init();
	uart_init();
	timer_init();
	

	//Ϊ��ֹ��һ�ζ��������ȶ�ȡһ���¶�
	tck_read_temp1();
	tck_read_temp2();

	while(1){

		//��ӡ������Ϣ
		if(DEBUG){
			printf("--------------------DEBUG--------------------\n");
			printf("T1: %d \n", (int)t1);
			printf("T2: %d \n", (int)t2);
			printf("T1 Max: %d \n", (int)t1max);
			printf("T2 Max: %d \n", (int)t2max);
			printf("--------------------DEBUG--------------------\n\n");
			delay(100);
		}

		/***************** set/confirm set START ********************/
		//����/Ӧ������
		if(!key_set){
			//����������״̬ʱ���ٴΰ������ð�ť�����ý���
			if(is_setting){
				is_setting = 0;
				is_read = 1;
				display();	
			}else{
				//��������ģʽ�������¶�
				is_setting = 1;
				is_read = 0;
				//��ʾ������Ϣ
				lcd_clear();
				lcd_display_string(1, 1, "SETTING..");
				if(set_road == 0){
					lcd_display_string(2, 1, "!T1 = ");
					lcd_display_string(2, 7, get_str(t1max));
				}else{
					lcd_display_string(2, 1, "!T2 = ");
					lcd_display_string(2, 7, get_str(t2max));
				}	
			}

			while(!key_set);		//�ȴ������ɿ�
			if(!is_setting){
				set_road = !set_road;	//�´�����ʱ��������һ·	
			}			
		}
		/***************** set/confirm set END ********************/

	   	//����/��С�����¶�
		/***************** up/down START ********************/
		if(is_setting){
			if(!(!key_up && !key_down)){
				//���󱨾��¶�
				if(!key_up){
					//��������������������
					delay(255);
					if(!key_up){
						if(set_road == 0){
							t1max++;
							lcd_display_string(2, 1, "!T1 = ");
							lcd_display_string(2, 7, get_str(t1max));
						}else{
							t2max++;
							lcd_display_string(2, 1, "!T2 = ");
							lcd_display_string(2, 7, get_str(t2max));
						}
					}	
				}

				//��С�����¶�
				if(!key_down){
					delay(255);
					if(!key_down){
						if(set_road == 0){
							t1max--;
							lcd_display_string(2, 1, "!T1 = ");
							lcd_display_string(2, 7, get_str(t1max));
						}else{
							t2max--;
							lcd_display_string(2, 1, "!T2 = ");
							lcd_display_string(2, 7, get_str(t2max));
						}
					}
				}
			}	
		}
		/***************** up/down END ********************/	


	   	/***************** read/display START ********************/
		if(is_read){
			temp1 = tck_read_temp1();		
			temp2 = tck_read_temp2();
		}

		//���¶�ֵ�����ı�ʱ����������ʾ
		if(temp1 != t1 || temp2 != t2){
			t1 = temp1;
			t2 = temp2;
			display();
		}
		/***************** read/display END ********************/

		/****************** warning START ******************/
		//��·�¶ȣ���һ·�����򱨾����������ù��̶�̬���ڱ���ֵ��
		if(!is_setting){
			if(t1 > t1max || t2 > t2max){
				buz = 0;
				timer_stop();
				oven = 0;
			}else{
				buz = 1;
				timer_start();
			}	
		}	
		

		/****************** warning END ******************/

	}
			
}

//��oven����
void timer_timeout(){
	oven = ~oven;
}

//��ʾ1·�¶ȡ�2·�¶ȡ�1·����ֵ��2·����ֵ
void display(){
	char t1str[8], t2str[8], t1maxstr[8], t2maxstr[8];
	lcd_clear();

	//��ʾ�¶�ֵ
	sprintf(t1str, "T1: %d", (int)t1);
	sprintf(t2str, "T2: %d", (int)t2);
	lcd_display_string(1, 1, t1str);
	lcd_display_string(1, 9, t2str);
	
	//��ʾ�����¶�ֵ
	sprintf(t1maxstr, "!T1: %d", (int)t1max);
	sprintf(t2maxstr, "!T2: %d", (int)t2max);
	lcd_display_string(2, 1, t1maxstr);
	lcd_display_string(2, 9, t2maxstr);
}

//������ת��Ϊ�ַ���
char* get_str(int val){
	char *str;
	if(val <= 9){
		char arr[1];
		str = arr;
	}else if(val <= 99){
		char arr[2];
		str = arr;
	}else if(val <= 999){
		char arr[3];
		str = arr;
	}else if(val <= 9999){
		char arr[4];
		str = arr;
	}else if(val <= 99999){
		char arr[5];
		str = arr;
	}
	sprintf(str, "%d", val);
	return str;
}

//������ʱ
void delay(uchar t){
	uchar i, j;
	for(i=0;i<t;i++)
		for(j=0;j<110;j++);
}

//printf�ض���
char putchar (char ch){
	uart_send(ch);
	return ch;
}


