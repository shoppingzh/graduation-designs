#include "reg52.h"
#include "fpm10a.h"
#include "lcd12864.h"
#include "intrins.h"

#define MAX_NUM 20

sbit key_store = P2^0;
sbit key_take = P2^1;
sbit key_close = P2^2;
sbit relay = P2^3;

idata uchar map[MAX_NUM];

void boot();
void home();
uchar get_unuse();
void wait_finger();
void store();
void take();
void do_store();
void do_take();

//��ͨ��ʱ ms
static void delayms(uint t){
	uint i, j;
	for(i=0;i<t;i++)
		for(j=0;j<110;j++);
}

//����ȴ���ʱ
static void delay2s(){
    uchar a,b,c;
    for(c=127;c>0;c--)
        for(b=235;b>0;b--)
            for(a=32;a>0;a--);
    _nop_();
}

void main(){

	lcd_init();
	fpm_init();
	home();

	while(1){
		 if(!key_store){
		 	store();
			while(!key_store);
		 }
		 if(!key_take){
		 	take();
		 	while(!key_take);
		 }
		 if(!key_close){
		 	//����
			relay = 1;
		 	while(!key_close);
		 }
		
			
	}
}



/**
* ��ȡ��ǰ������ӳ�䣬ӳ���ϵ����ǰ��� = �Ƿ�ʹ��
* 1Ϊʹ���У�0Ϊδʹ��
*/
static void get_map(){
	uchar i, *table, idx = 0;
	//��ȡ����ҳ0��������
	table = fpm_read_index_table(0);
	for(i=0;i<32;i++){
		//��ȡ����������ָ��ģ�������������Ӧ��ӳ�����
		uchar j;
		if(idx >= MAX_NUM)
			break;

		for(j=0;j<8;j++){
			if(idx >= MAX_NUM)
				break;
			if(table[i] & 0x01){
				map[idx] = 1;
			}else{
				map[idx] = 0;
			}
			table[i] >>= 1;
			idx++;
		}			
	}		
}

/**
* ��ȡδʹ�ù���
*/
uchar get_unuse(){
	uchar i, cnt;
	get_map();
	for(i=0;i<MAX_NUM;i++){
		if(map[i] == 0)
			cnt++;	
	}
	
	return cnt;	
}

//�ȴ��û�����ָ
void wait_finger(){
	//while(fpm_genimg() != 0x00);
	while(1){
		if(fpm_genimg() == 0x00)
			break;
		delayms(50);
	}
}

/**
* ��ȡ�洢��������N���չ���������������С�Ĺ���
*/
static uchar get_store_index(){
	uchar i;
	get_map();
	for(i=0;i<MAX_NUM;i++){
		if(map[i] == 0){
			return i;
		}		
	}
	return 0;	
}

//����
void boot(){
//	uchar i;
//	for(i=0;i<2;i++){
//		lcd_clear();
//		lcd_display_string(2, 3, "��ʼ��");
//		lcd_display_ascii(2, 6, '.', ' ');
//		delayms(400);
//		lcd_display_string(2, 3, "��ʼ��");
//		lcd_display_ascii(2, 6, '.', '.');
//		delayms(400);
//		lcd_display_string(2, 3, "��ʼ��");
//		lcd_display_ascii(2, 6, '.', '.');
//		lcd_display_ascii(2, 7, '.', ' ');
//		delayms(400);
//	}
}

//������	  	
void home(){
	delayms(10);
	lcd_clear();
	lcd_display_string(1, 3, "��ӭʹ��");
	lcd_display_string(2, 1, "ָ���Զ������");
	lcd_display_string(4, 2, "��ǰ�չ�");
	lcd_display_digit(4, 7, get_unuse());	
}

//���
static void do_store(){
	uchar temp, index;
 	temp = fpm_add_template((index = get_store_index()));
	lcd_clear();
	if(temp == 0x00){
		relay = 0;
		lcd_display_digit(2, 2, index+1);
		lcd_display_string(2, 3, "�����Ѵ򿪣�");
		lcd_display_string(3, 3, "��ӭʹ�ã�");
	}else if(temp == 0x02){
	   	lcd_display_string(2, 3, "��û��");
		lcd_display_string(3, 2, "������ָŶ��");
	}else if(temp == 0x24){
	   	lcd_display_string(2, 2, "���Ѿ�����ˣ�");
	}
	delay2s();
	home();
}

//ȡ��
static void do_take(){
	int index = fpm_auto_search(0, MAX_NUM-1);

	lcd_clear();
	if(index == -1){
		lcd_display_string(2, 2, "��û�д����");	
	}else{
		relay = 0;
		lcd_display_digit(2, 2, index+1);
		lcd_display_string(2, 3, "�����Ѵ򿪣�");
		lcd_display_string(3, 1, "��ȡ�����������");
		fpm_delete_template(index);	
	}

	delay2s();
	home();
}

//���
void store(){
	//�ж��Ƿ��пչ�
	if(get_unuse() <= 0){
		lcd_clear();
		lcd_display_string(2, 2, "��ǰû�пչ�");
		lcd_display_string(3, 3, "�������Ⱥ�");
		//�ȴ�2s����������
		delay2s();
		home();
		return;
	}

	lcd_clear();
	lcd_display_string(1, 4, "���");
	lcd_display_string(3, 1, "�����������ָ");
	lcd_display_ascii(3, 8, '.', '.');

	//�ȴ��û�������ָ
	wait_finger();
	do_store();	
}

//ȡ��
void take(){
	lcd_clear();
	lcd_display_string(1, 4, "ȡ��");
	lcd_display_string(3, 1, "�����������ָ");
	lcd_display_ascii(3, 8, '.', '.');

	//�ȴ��û�����ָ
	wait_finger();
 	do_take();
}

