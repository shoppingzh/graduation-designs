#include "reg52.h"
#include "uart.h"
#include "fpm10a.h"
#include "lcd1602.h"
#include "intrins.h"

#define MAX_NUM 30
#define MODE_NONE 0
#define MODE_NORMAL 1
#define MODE_COLLECTION 2

#define ERROR_COLLECTION_EXISTS 0x01

void wait_finger();
void do_signin();
void do_add();

idata uchar map[MAX_NUM];
uchar mode = MODE_NONE;
sbit key_sign = P3^3;
sbit key_clear = P2^0;

//��ͨ��ʱ ms
static void delayms(uint t){
	uint i, j;
	for(i=0;i<t;i++)
		for(j=0;j<110;j++);
}

//�ȴ�2s
static void delay2s(void)  {
    uchar a,b,c;
    for(c=127;c>0;c--)
        for(b=235;b>0;b--)
            for(a=32;a>0;a--);
    _nop_(); 
}


//���ʹ洢��ģ������
static void send_store_idx(uchar idx){
	uart_send(0x55);
	uart_send(0xaa);
	uart_send(0x01);
	uart_send(idx);
	uart_send(0xaa);
	uart_send(0x55);		
}

//����ǩ����ģ������
static void send_sign_idx(int idx){
	uart_send(0x55);
	uart_send(0xaa);
	uart_send(0x02);
	uart_send(idx);
	uart_send(0xaa);
	uart_send(0x55);
}

//���ʹ�����Ϣ
static void send_error_message(uchar error){
 	uart_send(0x55);
	uart_send(0xaa);
	uart_send(0xff);
	uart_send(error);
	uart_send(0xaa);
	uart_send(0x55);
}

//������
static void home(){
	lcd_clear();
	lcd_display_string(1, 5, "Hello!");
	lcd_display_string(2, 1, "Key1 --> Sign in");
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
* ��ȡ�洢����
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

/*****************************************************************************************/
/****************************************** MAIN *****************************************/
/*****************************************************************************************/
void main(){

	uart_init();
	lcd_simple_init();
	home();
	fpm_init();

	while(1){

		if(!key_sign){
			mode = MODE_NORMAL;
			while(!key_sign);	
		}

		if(!key_clear){
			fpm_clear_lib();
			while(!key_clear);	
		}

		if(mode == MODE_NORMAL){
			lcd_clear();
			lcd_display_string(1, 5, "Sign in");
			wait_finger();	 
			do_signin();
			mode = MODE_NONE;
			
			delay2s();
			home();			
		}else if(mode == MODE_COLLECTION){
			lcd_clear();
			lcd_display_string(1, 1, "Add new employee..");
			wait_finger();
			do_add();
			mode = MODE_NONE;
			
			delay2s();
			home();		
		}
	
	}
}

//���ڽ��ջص�
void uart_received(char cmd){
	if(cmd == 0x01){
		mode = MODE_COLLECTION;
	}
}

//�ȴ��û�����ָ
void wait_finger(){
	while(1){
		if(fpm_genimg() == 0x00)
			break;
		delayms(50);
	}
}

//ǩ��
void do_signin(){
	int idx = fpm_auto_search(0, MAX_NUM-1);
	if(idx != -1){
		lcd_clear();
		lcd_display_string(1, 4, "Success!");
		send_sign_idx(idx);
	}else{
		lcd_clear();
		lcd_display_string(1, 1, "You are not an");
		lcd_display_string(2, 1, "employee!");
	}
}

//���Ա��
void do_add(){
 	uchar idx, c;
	idx = get_store_index();
	c = fpm_add_template(idx);
	if(c == 0x00){
		lcd_clear();
		lcd_display_string(1, 4, "Success!");
		send_store_idx(idx);
	}else if(c == 0x24){
		lcd_clear();
		lcd_display_string(1, 1, "You're already ");
		lcd_display_string(2, 1, "an employee!");
		send_error_message(ERROR_COLLECTION_EXISTS);
	}
	
}
