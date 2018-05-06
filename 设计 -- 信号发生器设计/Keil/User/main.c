#include "reg51.h"
#include "signal_generator.h"
#include "uart.h"
#include "lcd12864.h"

#define uchar unsigned char
code uchar tips[] = "等候上位机指令";
code uchar str_squ[] = "当前波形：方波";
code uchar str_tra[] = "当前波形：叁角波";
code uchar str_sin[] = "当前波形：余弦波";
code uchar str_saw[] = "当前波形：锯齿波";

code uchar rob[] = {0x08,0x10,0x08,0x10,0x08,0x10,0x7F,0xFE,0x20,0x04,0x12,0x48,0x08,0x10,0x05,0xA0,0x02,0x40,0x01,0x80,0x01,0x80,0x07,0xE0,0x09,0x90,0x11,0x88,0x11,0x88,0x11,0x88}; 

void main(){
	uart_init();

	signal_generator_init();
	lcd_display_string(4, 1, tips);
	while(1){
	}
}

void display(uchar w){
	if(w == 1){
		lcd_display_string(4, 1, str_squ);	
	}else if(w == 2){
		lcd_display_string(4, 1, str_tra);
	}else if(w == 3){
		lcd_display_string(4, 1, str_sin);
	}else if(w == 4){
		lcd_display_string(4, 1, str_saw);
	}	
}

void uart_received(uchar cmd){
	uchar wave = cmd >> 4;
	uchar freq = cmd & 0x0f;
	uart_send(wave);
	if(wave == 1){
		signal_generator_quare(freq);	
	}else if(wave == 2){
		signal_generator_traingle(freq);
	}else if(wave == 3){
		signal_generator_sin(freq);
	}else if(wave == 4){
		signal_generator_sawtooth(freq);
	}
	display(wave);	
}

