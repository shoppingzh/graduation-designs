#include "reg52.h"
#include "lcd12864.h"
#include "intrins.h"
#include "adc.h"

#define trigger(d) (d < 127)	//�Ƿ񴥷�����������Ϊ��ס��
#define DEBUG 0					//����ģʽ
#define MAX_VALID_PEOPLE 50		//�����������

void delay(uint t);
void collect();
void analyse();
void check();

void home_page();
void setting_page();
void set_success_page();

sbit AD_CHANNEL = P3^3;			//ADͨ��
sbit relay = P3^0;				//�̵���
sbit buzzer = P3^1;				//������
sbit key_set = P3^5;			//���ü�
sbit key_up = P3^6;				//�Ӽ�
sbit key_down = P3^7;			//����

volatile uchar o1, o2; 			//����ͨ���ɼ�����ֵ
int people = 0;	  				//��������
uchar flag_in, flag_out; 		//�������̱�־
bit inout = 0;		   			//������־λ
int overload_people = 10;   	//��������
bit setting = 0; 				//����״̬��־λ

/**
* ��ҳ
*/
void home_page(){
	lcd_display_string(1, 2, "ʵʱ�����Ϣ");

	lcd_display_string(2, 1, "���ڳ˿ͣ�");
	lcd_display_digit(2, 6, people);
	lcd_display_string(2, 7, "��");

	lcd_display_string(3, 1, "���س˿ͣ�");
	lcd_display_digit(3, 6, overload_people);
	lcd_display_string(3, 7, "��");
}

/**
* ����ҳ��
*/
void setting_page(){
	lcd_clear();
	lcd_display_string(1, 1, "��ǰ���س˿ͣ�");
	lcd_display_digit(1, 8, overload_people);
	lcd_display_string(3, 1, "�����ϡ��¼�����");
	lcd_display_string(4, 1, "��������س˿�");
}

/**
* ���óɹ�����
*/
void set_success_page(){
	lcd_clear();
	lcd_display_string(2, 3, "���óɹ���");
}

/////////////////////////////////////////////MAIN
void main(){

	lcd_init();
	adc_init();
   	home_page();

	while(1){
	
		//�������
		if(!key_set){
			setting = ~setting;
			if(setting){
				setting_page();
			}else{
				set_success_page();	
				delay(1000);
				home_page();
			}
			while(!key_set);	
		}

		if(setting){
		 	if(!(!key_up && !key_down)){
				if(!key_up){
					delay(50);
					if(!key_up){
						if(overload_people < MAX_VALID_PEOPLE){
							overload_people++;
							setting_page();
						}		
					}
				}
				if(!key_down){
					delay(50);
					if(!key_down){
						if(overload_people > 1){
							overload_people--;
							setting_page();
						}		
					}
				}
			}	
		}else{
			collect();
			analyse();
			check();

			if(DEBUG){
				lcd_clear_line(2);
				lcd_clear_line(3);
	
				lcd_display_string(2, 1, "ģ����һ��");
				lcd_display_digit(2, 6, (int)o1);
				lcd_display_string(3, 1, "ģ��������");
				lcd_display_digit(3, 6, (int)o2);
			}
		}		
	}


}

/**
* ��ͨ��ʱ��ms��
*/
void delay(uint t){
    uint a,b;
    for(a=0;a<t;a++)
		for(b=0;b<110;b++);
}

/**
* �ɼ���·������
*/
void collect(){
	uchar i;

	AD_CHANNEL = 0;
	delay(5);
	for(i=0;i<10;i++){
		o1 = adc_transform();
	}

	AD_CHANNEL = 1;
	delay(5);
	for(i=0;i<10;i++){
		o2 = adc_transform();	
	}	
}

/**
* ��ӡ������Ϣ
*/
static void debug_msg(char *str){
	lcd_clear_line(4);
	lcd_display_string(4, 1, str);
}

/**
* ���ݴ������Ĵ���˳��������³����
*/
void analyse(){
	bit update = 0;
	if(o1 == 0 && o2 == 0)
		return;

	//������1�Ĵ���
	if(trigger(o1)){
		if(flag_in == 0 && flag_out == 0){
			inout = 0;
		}
		if(inout == 0){
			//�����浽������һ������������ʼ����
			if(flag_in == 0){
				flag_in = 1;
				if(DEBUG){
					debug_msg("��ʼ����");
				}	
			}
		}else{
			//���м䴥������һ������������������
			if(flag_out == 2){
				flag_out = 3;
				if(DEBUG){
					debug_msg("��������");
				}
			}
		}					
	}else{
		if(inout == 0){
			//������һ�������������������������м�
			if(flag_in == 1){
				flag_in = 2;
				if(DEBUG){
					debug_msg("λ���м�λ��");
				}
			} 
		}else{
			//�뿪��һ�����������߳����⣬������1
			if(flag_out == 3){
				flag_out = 0;
				if(people > 0){
					people--;
					update = 1;
					if(DEBUG){
						debug_msg("�߳�����");
					}
				}	
			}	
		}	
	}

	//������2�Ĵ���
	if(trigger(o2)){
		if(flag_in == 0 && flag_out == 0){
			inout = 1;			
		}
		if(inout == 0){
			//���м䴥�����ڶ�������������������
			if(flag_in == 2){
				flag_in = 3;
				if(DEBUG){
					debug_msg("��������");
				}
			}
		}else{
			//�����津�����ڶ�������������ʼ����
		   	if(flag_out == 0){
				flag_out = 1;
				if(DEBUG){
					debug_msg("��ʼ����");
				}
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
					if(DEBUG){
						debug_msg("��������");
					}
				}	
			}
		}else{
			//�뿪�ڶ��������������������������м�
			if(flag_out == 1){
				flag_out = 2;
				if(DEBUG){
					debug_msg("λ���м�λ��");
				}
			}	
		}	
	}


	//������Ҫ��ʾ������Ϣ
	if(update){
		home_page();	
	}
}

/**
* ����
*/
static void warning(){
	buzzer = ~buzzer;
	delay(1);
	buzzer = ~buzzer;
	delay(1);
}

/**
* ����Ƿ���
*/
void check(){
	if(people > overload_people){
		warning();
		relay = 0;			
	}else{
		relay = 1;
	}	
}