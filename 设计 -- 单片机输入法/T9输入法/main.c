#include "key.h"
#include "pyinput.h"
#include "string.h"
#include "lcd12864.h"
#include "intrins.h"
#include "stdio.h"

#ifndef uchar
	#define uchar unsigned char
#endif

char input_buffer[8];					//输入缓冲区，如："524"
int input_index = 0;					//当前输入缓冲区的位置

py_index *matchs[10];					//当前输入的拼音所匹配的所有汉字信息
char *opt_words;						//当前所有备选汉字，如"wang"对应"往网王忘汪望旺"
uchar opt_idx = 0;						//当前备选汉字索引
char page_words[9]; 					//当前页的备选汉字，1行只显示4个汉字，如"wang"对应"1.往2.网3.王4.忘"
uchar page = 0;							//页数，拼音匹配的汉字每4个汉字为1页，默认显示第一页
char words_buffer[65];					//屏幕汉字缓冲区
uchar words_idx = 0;					//汉字缓冲区索引，指示当前屏幕汉字的个数

uchar row = 0; 							//当前显示的行
uchar col = 1;						   	//当前显示的列

bit writing = 0;						//是否在书写状态
bit flag = 1;							//光标状态位
uchar count = 0;						//定时器计数

//普通延时
static void delay(uchar t){
	uchar i,j;
	for(i=0;i<t;i++)
		for(j=0;j<110;j++);
}


//清除缓冲区
static void clear_input_buffer(){
	uchar i;
	for(i=0;i<8;i++){
		input_buffer[i] = 0;
	}
}

//显示当前输入的拼音字符
static void show_letters(){
	uchar line[17], i, *py;
	//清空拼音显示行
	clearline(2);

	for(i=0;i<17;i++){
		line[i] = '\0';	
	}
	py = matchs[0][0].py;
	for(i=0;i<16;i++){
		if(! *py)
			continue;

		line[i] = *py;
		py++;		
	}
	displaystring(2, 0, line);
}

//显示备选字
static void show_options(){
	uchar start = page*8, i, page_content[17], idx = 0;
	opt_words = matchs[0][0].pymb;

	//清空当前页内容
	clearline(3);

	//跳过前面的页数
	for(i=0;i<start;i++){
		if(! *opt_words)
			break;
		opt_words++;
	}
	//获取当前页汉字
	strncpy(page_words, opt_words, 8);
	page_words[8] = '\0';
	//生成当前页内容，如："1.往2.网3.王4.忘"
	for(i=0;i<16;i++){
		uchar c = i / 2;
		//序号
		if(c % 2 == 0){
			//数字
			if(i % 2 == 0){
				uchar order = (i / 4) + 1;
				//如果当前属于备选，则不显示序号而是显示"*"
				if(order == opt_idx + 1){
					page_content[i] =  '*';
				}else{
					page_content[i] = order + 48;
				}	
			}else{
				//点
				page_content[i] = '.';
			}		
		}else{
			//汉字
			page_content[i] = page_words[idx++];
		}	
	}
	page_content[16] = '\0';	

	//显示当前页的内容
	displaystring(3, 0, page_content);
}

//上一页
static void prev_page(){
	if(page > 0){
		page--;
		opt_idx = 3;
	}		
}

//上一页
static void next_page(){
	page++;
	opt_idx = 0;
}

//在屏幕上写一个汉字
static void write_word(uchar *word){
	//写到行末
	if(col > 7){
		row++;
		col = 0;
		//文本框写满，重新来过
		if(row > 1){
			clearline(0);
			clearline(1);
			row = 0;
			col = 1;
		}
	}
	
	//显示当前汉字
	displaystring(row, col++, word);

	//将当前汉字存储到缓冲区
//	if(words_idx < 61){
//		words_buffer[words_idx++] = word[0];
//		words_buffer[words_idx++] = word[1];	
//	}	
}

//在屏幕上显示当前汉字
static void show_current(){
	uchar word[3] = {0, 0, 0}, idx;

	//获取当前汉字
	idx = opt_idx * 2;
	word[0] = page_words[idx];
	word[1] = page_words[idx + 1];

	write_word(word);	
}

//删除一个汉字
static void delete_word(){
	if(row >= 0){
		if(col > 0){
			col--;
		}else{
			if(row > 0){
				col = 7;
				row--;
			}
		}
	}
	displaystring(row, col, "  ");
}


//定时器初始化
static void timer_init(){
	TMOD = 0x01;
	TH0 = 0x3c;
	TL0 = 0xb0;
	EA = 1;
	ET0 = 1;
	//TR0 = 1;
}	   	

void main(){
	initlcm();
	displaystring(2, 0, "欢迎使用输入法，");
	displaystring(3, 0, "输入内容试试看！");

	timer_init();

	while(1){
		int key = keyscan();

		if(key == -1){
			//错误
		}else if(key == 0){	
			//不在书写状态按空格则在屏幕上书写一个空格
			if(!writing){
				write_word("  ");
				continue;	
			}
			//按下0键，将当前汉字显示到屏幕上
			show_current();			

			//清理
			clear_input_buffer();
			input_index = 0;
			opt_idx = 0;
			writing = 0;

			clearline(2);				
			clearline(3);			
		}else if(key == 1){
		 	//按下1键，开启或关闭光标
			if(TR0)
				TR0 = 0;
			else{
				TR0 = 1;
				displaystring(2, 2, "适用型功能，");
				displaystring(3, 0, "请谨慎使用！");
			} 
				
		}else if(key == 10){
			if(!writing){
				//如果当前不是在书写状态，按下*键删除一个屏幕上的已有汉字
				delete_word();
				continue;
			}

			//备选汉字列表左移一位
			if(opt_idx > 0){
				opt_idx--;
			}else{
				prev_page();
			}
			show_options();		
		}else if(key == 11){
			if(!writing){
				//全屏显示：显示汉字缓冲区的所有内容
				//full_screen();
				continue;	
			}
				
			//备选汉字列表右移一位
			if(opt_idx < 3){
				opt_idx++;
			}else{
				next_page();
			}
			show_options();
		}else{
			if(input_index > 5){
				continue;
			}
			writing = 1;
			page = 0;

			//正在输入，获取输入的拼音和汉字
			input_buffer[input_index++] = key + 48;
			get_matched_pymb(input_buffer, matchs);

			//显示输入的拼音字符
			show_letters();
			
			//显示备选字
			show_options();
		}
	}
}

//定时器0中断，用来显示光标
void timer0_int() interrupt 1{
	uchar r, c;
	TH0 = 0x3c;
	TL0 = 0xb0;
	if(count++ < 10)
		return;

	count = 0;

	//复制一份，防止row与col被动态更改
	r = row;
	c = col;

	if(flag){
		displaystring(r, c, "_");	
	}else{
		displaystring(r, c, "  ");
	}
	flag = ~flag;
	
}
