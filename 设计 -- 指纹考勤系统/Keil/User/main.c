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

//普通延时 ms
static void delayms(uint t){
	uint i, j;
	for(i=0;i<t;i++)
		for(j=0;j<110;j++);
}

//等待2s
static void delay2s(void)  {
    uchar a,b,c;
    for(c=127;c>0;c--)
        for(b=235;b>0;b--)
            for(a=32;a>0;a--);
    _nop_(); 
}


//发送存储的模板索引
static void send_store_idx(uchar idx){
	uart_send(0x55);
	uart_send(0xaa);
	uart_send(0x01);
	uart_send(idx);
	uart_send(0xaa);
	uart_send(0x55);		
}

//发送签到的模板索引
static void send_sign_idx(int idx){
	uart_send(0x55);
	uart_send(0xaa);
	uart_send(0x02);
	uart_send(idx);
	uart_send(0xaa);
	uart_send(0x55);
}

//发送错误信息
static void send_error_message(uchar error){
 	uart_send(0x55);
	uart_send(0xaa);
	uart_send(0xff);
	uart_send(error);
	uart_send(0xaa);
	uart_send(0x55);
}

//主界面
static void home(){
	lcd_clear();
	lcd_display_string(1, 5, "Hello!");
	lcd_display_string(2, 1, "Key1 --> Sign in");
}

/**
* 获取当前存包柜的映射，映射关系：当前柜号 = 是否使用
* 1为使用中，0为未使用
*/
static void get_map(){
	uchar i, *table, idx = 0;
	//读取索引页0的索引表
	table = fpm_read_index_table(0);
	for(i=0;i<32;i++){
		//获取索引表中有指纹模板的索引，存入应用映射表中
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
* 获取存储索引
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

//串口接收回调
void uart_received(char cmd){
	if(cmd == 0x01){
		mode = MODE_COLLECTION;
	}
}

//等待用户放手指
void wait_finger(){
	while(1){
		if(fpm_genimg() == 0x00)
			break;
		delayms(50);
	}
}

//签到
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

//添加员工
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
