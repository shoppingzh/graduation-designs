#include "reg51.h"
#include "intrins.h"
#define uchar unsigned char

uchar count = 0;
char i = 3;
code uchar t[] = {0xfc, 0xf9, 0xf3, 0xf6};

bit running = 0, dir = 0;

sbit key_run = P3^0;
sbit key_dir = P3^1;

void main(){

	TMOD = 0x01;
	TH0 = 0x3c;
	TL0 = 0xb0;
	EA = 1;
	ET0 = 1;
	TR0 = 1;

	while(1){
		if(!key_run){
			i = 0;
			running = ~running;
			while(!key_run);
		}
		if(!key_dir){
			i = 3;
			dir = ~dir;
			while(!key_dir);
		}
	}
}

void timer0_int() interrupt 1{
	TH0 = 0x3c;
	TL0 = 0xb0;

	if(count++ < 1){
		return;
	}
	count = 0;

	if(running){
		if(dir){
			if(i >= 4){
				i = 0;
			}
			P2 = t[i++];
			
		}else{
			if(i < 0){
				i = 3;
			}
			P2 = t[i--];
		}
	}
		
}