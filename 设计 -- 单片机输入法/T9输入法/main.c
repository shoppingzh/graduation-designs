#include "key.h"
#include "pyinput.h"
#include "string.h"
#include "lcd12864.h"
#include "intrins.h"
#include "stdio.h"

#define uchar unsigned char

char input_buffer[8] = {0, 0, 0, 0, 0, 0, 0, 0};
int input_index = 0;

uchar cursor = 0;
uchar line = 0;
uchar pos = 1;
uchar *words;

//普通延时
static void delay(uchar t){
	uchar i,j;
	for(i=0;i<t;i++)
		for(j=0;j<110;j++);
}



//切割临时输入字符串，得到实际的输入字符串
static char* trim(){
	char str[6];
	return strncpy(str, input_buffer, input_index);
}

//清除缓冲区
static void clear_input_buffer(){
	uchar i;
	for(i=0;i<8;i++){
		input_buffer[i] = 0;
	}
}	   	

void main(){

	//char* str;
	//char str2[15];
	//uchar c;
	py_index *matchlist[10];

	initlcm();

//	c = get_pymb("a");
//	sprintf(str, "%d", (int)c);
//	displaystring(3, 0, str);

	while(1){
		int key = keyscan();

		if(key == -1){
			//错误
		}else if(key == 0){
			//确认输入当前汉字
			uchar word[3];
			word[0] = words[cursor];
			word[1] = words[cursor+1];
			word[2] = '\0';
			
			if(pos > 7){
				line = 1;
				pos = 0;
			}
			displaystring(line, pos++, word);			

			clear_input_buffer();
			input_index = 0;
			cursor = 0;
			
			clearline(2);				
			clearline(3);				
		}else if(key == 10){
			//备选汉字列表左移一位
			cursor -= 2;			
		}else if(key == 11){
			//备选汉字列表右移一位
			cursor += 2;
			
		}else{
			if(input_index > 5){
				continue;
			}

			//正在输入，获取输入的拼音和汉字
			input_buffer[input_index++] = key + 48;
			get_matched_pymb(input_buffer, matchlist);

			words =  matchlist[0][0].pymb;

			clearline(2);
			displaystring(2, 0,  matchlist[0][0].py);
			
			displaystring(3, 0,  matchlist[0][0].pymb);
			
		}

		//显示
	}
}