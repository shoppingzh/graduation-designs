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

//普通延时 ms
static void delayms(uint t){
	uint i, j;
	for(i=0;i<t;i++)
		for(j=0;j<110;j++);
}

//界面等待延时
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
		 	//关门
			relay = 1;
		 	while(!key_close);
		 }
		
			
	}
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
* 获取未使用柜数
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

//等待用户放手指
void wait_finger(){
	//while(fpm_genimg() != 0x00);
	while(1){
		if(fpm_genimg() == 0x00)
			break;
		delayms(50);
	}
}

/**
* 获取存储索引：在N个空柜中找最索引号最小的柜子
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

//开机
void boot(){
//	uchar i;
//	for(i=0;i<2;i++){
//		lcd_clear();
//		lcd_display_string(2, 3, "初始化");
//		lcd_display_ascii(2, 6, '.', ' ');
//		delayms(400);
//		lcd_display_string(2, 3, "初始化");
//		lcd_display_ascii(2, 6, '.', '.');
//		delayms(400);
//		lcd_display_string(2, 3, "初始化");
//		lcd_display_ascii(2, 6, '.', '.');
//		lcd_display_ascii(2, 7, '.', ' ');
//		delayms(400);
//	}
}

//主界面	  	
void home(){
	delayms(10);
	lcd_clear();
	lcd_display_string(1, 3, "欢迎使用");
	lcd_display_string(2, 1, "指纹自动存包柜！");
	lcd_display_string(4, 2, "当前空柜：");
	lcd_display_digit(4, 7, get_unuse());	
}

//存包
static void do_store(){
	uchar temp, index;
 	temp = fpm_add_template((index = get_store_index()));
	lcd_clear();
	if(temp == 0x00){
		relay = 0;
		lcd_display_digit(2, 2, index+1);
		lcd_display_string(2, 3, "号门已打开！");
		lcd_display_string(3, 3, "欢迎使用！");
	}else if(temp == 0x02){
	   	lcd_display_string(2, 3, "您没有");
		lcd_display_string(3, 2, "按下手指哦！");
	}else if(temp == 0x24){
	   	lcd_display_string(2, 2, "您已经存包了！");
	}
	delay2s();
	home();
}

//取包
static void do_take(){
	int index = fpm_auto_search(0, MAX_NUM-1);

	lcd_clear();
	if(index == -1){
		lcd_display_string(2, 2, "您没有存包！");	
	}else{
		relay = 0;
		lcd_display_digit(2, 2, index+1);
		lcd_display_string(2, 3, "号门已打开！");
		lcd_display_string(3, 1, "请取走您的物件！");
		fpm_delete_template(index);	
	}

	delay2s();
	home();
}

//存包
void store(){
	//判断是否有空柜
	if(get_unuse() <= 0){
		lcd_clear();
		lcd_display_string(2, 2, "当前没有空柜");
		lcd_display_string(3, 3, "请稍作等候！");
		//等待2s，回主界面
		delay2s();
		home();
		return;
	}

	lcd_clear();
	lcd_display_string(1, 4, "存包");
	lcd_display_string(3, 1, "请放入您的手指");
	lcd_display_ascii(3, 8, '.', '.');

	//等待用户按下手指
	wait_finger();
	do_store();	
}

//取包
void take(){
	lcd_clear();
	lcd_display_string(1, 4, "取包");
	lcd_display_string(3, 1, "请放入您的手指");
	lcd_display_ascii(3, 8, '.', '.');

	//等待用户按手指
	wait_finger();
 	do_take();
}

