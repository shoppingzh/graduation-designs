#include "ds18b20.h"
#include "reg51.h"
#include "intrins.h"
#include "uart.h"

sbit DQ = P3^6;
uchar num = 0;		//DS18B20的数量
uchar ids[MAX_NUM][8];

void delay(uchar i){
	do{
		_nop_();
		_nop_();
		_nop_();
		i--;
	}while(i);
}

void ds18b20_init(){
	uchar x = 0;
	DQ = 1;		  
	delay(10);	  
	DQ = 0;		 
	delay(120);	  
	DQ = 1;		 
	delay(16);	 
	x = DQ;		
	delay(80);	
	DQ = 1;		
	P0 = x;
}

void ds18b20_write_bit(uchar b){
	DQ = 0;
	DQ = b&0x01;			
	delay(12);				 
	DQ = 1;
	delay(5);	
}

void ds18b20_write(uchar byte){
	uchar i = 0;
	for(i=8;i>0;i--){
		ds18b20_write_bit(byte & 0x01);
		byte >>= 1;
	}	
}

uchar ds18b20_read_bit(){
	uchar bt;
	DQ = 0;				
	delay(1);			
	DQ = 1;					
	if(DQ)			
		bt = 0x01;		
	delay(11);

	return bt;
}

uchar ds18b20_read_2bits(){
	uchar i, b2;
	for(i=2;i>0;i--){
		DQ = 0;			
		delay(1);		
		DQ = 1;			
		b2 <<= 1;		
		if(DQ)			
			b2 |= 0x10;		
		delay(11);	
	}

	return b2;
}

uchar ds18b20_read(){
	uchar i, byte = 0;
	for(i=8;i>0;i--){
		DQ = 0;			
		delay(1);		
		DQ = 1;			
		byte >>= 1;		
		if(DQ)			
			byte |= 0x80;		
		delay(11);
	}
	return byte;	
}

uchar ds18b20_read_temp1(){
	uchar templ, temph, tt;
	uint t;
	ds18b20_init();		   
	ds18b20_write(0XCC);	   
	ds18b20_write(0x44);

	ds18b20_init();		 
	ds18b20_write(0xcc);	  
	ds18b20_write(0xbe);
		 
	templ=ds18b20_read();	 
	temph=ds18b20_read();	  
	t = temph;
	t <<= 8;
	t = t | templ;
	tt = t * 0.0625;
			  
	return tt;			   
}

uchar* ds18b20_read_rom(){
	uchar i, rom[8];

	//串口初始化
	uart_init();

	ds18b20_init();
	ds18b20_write(0x33);

	for(i=0;i<8;i++){
		rom[i] = ds18b20_read();
	}

	return rom;
}
