#include "reg52.h"
#include "lcd1602.h"
#include "adc.h"
#include "stdio.h"
#include "intrins.h"

#define DEFAULT_OVER_WEIGHT 80
#define get_w(v) ((115 - 15) * 1.0f / (243 - 13) * v + 10)

uchar get(uchar channel);
uchar avg();

sbit ADDA = P3^2;
sbit ADDB = P3^3;
sbit ADDC = P3^4;
sbit key_set = P3^5;
sbit key_up = P3^6;
sbit key_down = P3^7;
sbit ctrl = P3^0;
sbit warning = P3^1;

uchar weight;
bit setting = 0;
uchar over_weight = DEFAULT_OVER_WEIGHT;

//ѡ��ģ��ͨ��
static void choose(uchar channel){
	switch(channel){
		case 0:
			ADDA = 0;ADDB = 0;ADDC = 0;
			break;
		case 1:
			ADDA = 1;ADDB = 0;ADDC = 0;
			break;
		case 2:
			ADDA = 0;ADDB = 1;ADDC = 0;
			break;
		case 3:
			ADDA = 1;ADDB = 1;ADDC = 0;
			break;
		case 4:	 
			ADDA = 0;ADDB = 0;ADDC = 1;
			break;
		default:
			ADDA = 0;ADDB = 0;ADDC = 0;
			break;
	}
}

//��ͨ��ʱ
static void delay(uint t){
	uint i, j;
	for(i=0;i<t;i++){
		for(j=0;j<110;j++);
	}
}

//���ý���
static void setting_page(){
	uchar str[16];
	lcd_display_string(1, 1, "Set max weight: ");
	sprintf(str, "%16d", (int)over_weight);
	lcd_display_string(2, 1, str);		

}

//�������� force: �Ƿ�ǿ����ʾ
static void working_page(uchar force){
	uchar str[16], curr;
	curr = avg();		
	if(curr != weight || force){
		lcd_clear();

		//��ʾ��ǰ����
		weight = curr;
		sprintf(str, "Weight: %d", (int)weight);
		lcd_display_string(1, 1, str);

		//��ʾ������Ϣ
		if(weight > over_weight){
			lcd_display_string(2, 1, "Overweight: Yes");
		}else{
			lcd_display_string(2, 1, "Overweight: No");
		}
	}
}


void main(){
	lcd_simple_init();
	ctrl = 0;

	while(1){

		if(!key_set){
			if(setting){
				//ȷ������
				lcd_clear();
				setting = 0;
				working_page(1);
			}else{
				//��������
				lcd_clear();
				setting = 1;
				setting_page();
			}

			while(!key_set);
		}
		
		if(setting){
			if(!key_up){
				delay(100);
				if(!key_up){
					if(over_weight < 115){
						over_weight++;
						setting_page();
					}		
				}
			}
			if(!key_down){
				delay(100);
				if(!key_down){
					if(over_weight > 0){
						over_weight--;
						setting_page();
					}	
				}
			}			
		}else{
			working_page(0);
			if(weight > over_weight){
				warning = 0;
				ctrl = 1;	
			}else{
				warning = 1;
				ctrl = 0;
			}	
		}
	}
}

/**
* ��ȡĳ·������
*/
uchar get(uchar channel){
	uchar i;
	choose(channel);
	delay(5);
	for(i=0;i<10;i++){
		adc_transform();
	}	

	return get_w(adc_transform());
}

/**
* ��ȡ5·����ֵ��ƽ��ֵ
*/
uchar avg(){
	uchar w0, w1, w2, w3, w4;
	uint sum;
	w0 = get(0);
	w1 = get(1);
	w2 = get(2);
	w3 = get(3);
	w4 = get(4);
	sum = w0 + w1 + w2 + w3 + w4;

	return sum / 5;
}

