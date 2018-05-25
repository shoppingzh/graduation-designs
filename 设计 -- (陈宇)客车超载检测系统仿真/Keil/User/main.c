#include "reg51.h"
#include "adc.h"
#include "lcd1602.h"
#include "stdio.h"
#include "intrins.h"

#define MAX_DISTANCE 40
#define MAX_VALID_PEOPLE 50
#define cal(ad) ((1.0f / (ad * 0.0005f + 0.00158f)) - 7)		//AD --> ����ת����ʽ
#define trigger(distance) (distance < MAX_DISTANCE)

void delay(uint t);
void get_distance();
void analyse();
void display_inside();
void display_max();

sbit ADDA = P2^7;
sbit key_set = P3^0;
sbit key_up = P3^1;
sbit key_down = P3^2;
sbit warning = P3^3;
sbit control = P3^4;

float d1, d2;					//d1/d2����һ���������������ɼ����ľ���
int people = 0;					//��������
uchar flag_in, flag_out;		//�������̱�־
bit inout = 0;					//������ı�־λ��Ϊ0ʱΪ����Ϊ1ʱΪ����
int max_people = 0;				//��������
bit setting = 1;				//�Ƿ�������״̬


void main(){
	lcd_simple_init();
	lcd_display_string(1, 1, "Init Setting: ");
	ADDA = 0;
	control = 0;

	while(1){

		//����/�˳�����
		if(!key_set){
			setting = ~setting;
			if(setting){
				char str[16];
				sprintf(str, "Max Overload:%d", max_people);
				lcd_clear();
				lcd_display_string(1, 1, "Setting..");
				lcd_display_string(2, 1, str);

			}else{
				display_inside();
			}
			while(!key_set);	
		}

		//����/���������������
		if(setting){
			if(!(!key_up && !key_down)){
				if(!key_up){
					delay(100);
					if(!key_up){
						if(max_people < MAX_VALID_PEOPLE){
							max_people++;
							display_max();
						}		
					}
				}
				if(!key_down){
					delay(100);
					if(!key_down){
						if(max_people > 1){
							max_people--;
							display_max();
						}		
					}
				}
			}		
		}else{
			//����״̬
		   	get_distance();
			analyse();
			if(people > max_people){
				warning = 0;
				control = 1;			
			}else{
				warning = 1;
				control = 0;
			}
		}
	}
}

void display_max(){
	uchar str[16];
	lcd_display_string(1, 1, "Max Overload: ");
	sprintf(str, "%16d", max_people);
	lcd_display_string(2, 1, str);
}

/**
* �������ɼ��л���ʱ
*/
void delay(uint t){
    uint a,b;
    for(a=0;a<t;a++)
		for(b=0;b<110;b++);
}

/**
* ��ȡ�����������ɼ����ľ���
*/
void get_distance(){
	uchar i;
	ADDA = 0;
	delay(1);
	for(i=0;i<3;i++){
	   d1 = cal(adc_transform());
	}

	ADDA = 1;
   	delay(1);
	for(i=0;i<3;i++){
	   d2 = cal(adc_transform());
	}
}

/**
* ��ʾ��ǰ��������
*/
void display_inside(){
	uchar str[16];
	sprintf(str, "Inside: %d", (int)people);
	lcd_clear();
	lcd_display_string(1, 1, str);
}

/**
* ���ݴ������Ĵ���˳��������³����
*/
void analyse(){
	bit update = 0;
	if(d1 == 0 || d2 == 0)
		return;

	//������1�Ĵ���
	if(trigger(d1)){
		if(flag_in == 0 && flag_out == 0){
			inout = 0;
		}
		if(inout == 0){
			//�����浽������һ������������ʼ����
			if(flag_in == 0){
				flag_in = 1;	
			}
		}else{
			//���м䴥������һ������������������
			if(flag_out == 2){
				flag_out = 3;
			}
		}					
	}else{
		if(inout == 0){
			//������һ�������������������������м�
			if(flag_in == 1){
				flag_in = 2;
			} 
		}else{
			//�뿪��һ�����������߳����⣬������1
			if(flag_out == 3){
				flag_out = 0;
				if(people > 0){
					people--;
					update = 1;
				}	
			}	
		}	
	}

	//������2�Ĵ���
	if(trigger(d2)){
		if(flag_in == 0 && flag_out == 0){
			inout = 1;			
		}
		if(inout == 0){
			//���м䴥�����ڶ�������������������
			if(flag_in == 2){
				flag_in = 3;
			}
		}else{
			//�����津�����ڶ�������������ʼ����
		   	if(flag_out == 0){
				flag_out = 1;
			}
		}						
	}else{
		if(inout == 0){
			//�뿪�ڶ������������������ڣ�������1
		 	if(flag_in == 3){
				flag_in = 0;
				if(people < 255){
					people++;
					update = 1;
				}	
			}
		}else{
			//�뿪�ڶ��������������������������м�
			if(flag_out == 1){
				flag_out = 2;
			}	
		}	
	}


	//������Ҫ��ʾ������Ϣ
	if(update){
		display_inside();	
	}
}
