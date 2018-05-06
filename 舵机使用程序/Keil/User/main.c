#include "reg51.h"
#include "intrins.h"

#define uchar unsigned char

sbit PWN = P2^0;
bit flag;
uchar count;

sbit key = P3^5;

void main(){

	PWN = 0;

	TMOD = 0x01;
	TH0 = 0xfe;
	TL0 = 0x33;
	EA = 1;
	ET0 = 1;
	TR0 = 1;

	while(1){
		if(!key){
			flag = !flag;
			while(!key);
		}
	}

}

void timer_int() interrupt 1{
	TH0 = 0xfe;
	TL0 = 0x33;
	if(count == 0){
		//给高脉冲
		PWN = 1;
	}
	if(flag){
		if(count == 1){
			PWN = 0;
		}
	}else{
		if(count == 5){
			PWN = 0;
		}
	}
	
	if(count++ >= 40){
		count = 0;
		//脉冲周期到
	}
}
