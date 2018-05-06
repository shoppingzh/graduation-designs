#include "reg51.h"

sbit key = P2^0;

void main(){
	
	key = 0;

	TMOD = 0x01;
	TH0 = 0x3c;
	TL0 = 0xb0;
	EA = 1;
	ET0 = 1;
	TR0 = 1;
	while(1);	
}

void timer_int() interrupt 1{
	key = !key;
}
