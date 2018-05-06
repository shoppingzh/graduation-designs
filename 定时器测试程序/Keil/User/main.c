#include "reg51.h"

sbit led = P3^5;

void main(){

	TMOD = 0x01;
	TH0 = 0xff;
	TL0 = 0xce;
	EA = 1;
	ET0 = 1;
	TR0 = 1;
	while(1);
}

void timer_int() interrupt 1{
	TH0 = 0xff;
	TL0 = 0xce;
	led = !led;
}
