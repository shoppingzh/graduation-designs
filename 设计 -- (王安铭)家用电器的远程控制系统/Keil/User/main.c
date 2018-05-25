#include "reg52.h"
#include "uart.h"

void timer_init();

sbit led_hall = P1^0;
sbit led_bedroom = P1^1;
sbit fan = P0^0;

uchar count = 0;
uchar max_count = 100;
float rate = 1;


void main(){
 	uart_init();
	timer_init();

	while(1);
}

/**
* 定时器初始化
*/
void timer_init(){
	TMOD |= 0x01;
	TH0 = 0xff;
	TL0 = 0xa4;
	EA = 1;
	ET0 = 1;
}

static void bedroom_led(uchar lightness){
	if(lightness == 0){
		TR0 = 0;
		return;
	}

	TR0 = 1;
	rate = lightness / 100.0;
	count = 0;	
}

void timer_int() interrupt 1{
	TH0 = 0xff;
	TL0 = 0xa4;
	if(count > max_count){
		count = 0;
	}

	if(count == 0){
		led_bedroom = 0;
	}else if(count == (max_count * rate)){
		led_bedroom = 1;	
	}
	
	count++;	
}

void uart_received(uchar cmd){
	if(cmd == 0){
		//大厅灯关
		led_hall = 1;
	}else if(cmd == 1){
		//大厅灯开
		led_hall = 0;
	}else if(cmd > 1 && cmd < 102){
		bedroom_led(cmd - 2);
	}else if(cmd == 102){
		fan = 1;
	}else if(cmd == 103){
		fan = 0;
	}  	
}
