#include "ds18b20.h"
#include "reg51.h"
#include "intrins.h"
#include "uart.h"

sbit DQ1 = P2^0;
sbit DQ2 = P2^1;
uchar num = 0;		//DS18B20µÄÊýÁ¿
uchar ids[MAX_NUM][8];

void delay(uchar i){
	do{
		_nop_();
		_nop_();
		_nop_();
		i--;
	}while(i);
}

void ds18b20_init1(){
	DQ1 = 1;		  
	delay(10);	  
	DQ1 = 0;		 
	delay(120);	  
	DQ1 = 1;		 
	delay(16);	 	
	delay(80);	
	DQ1 = 1;			
}

void ds18b20_init2(){
	DQ2 = 1;		  
	delay(10);	  
	DQ2 = 0;		 
	delay(120);	  
	DQ2 = 1;		 
	delay(16);	 	
	delay(80);	
	DQ2 = 1;	
}

void ds18b20_write_bit1(uchar b){
	DQ1 = 0;
	DQ1 = b&0x01;			
	delay(12);				 
	DQ1 = 1;
	delay(5);	
}

void ds18b20_write_bit2(uchar b){
	DQ2 = 0;
	DQ2 = b&0x01;			
	delay(12);				 
	DQ2 = 1;
	delay(5);	
}

void ds18b20_write1(uchar byte){
	uchar i = 0;
	for(i=8;i>0;i--){
		ds18b20_write_bit1(byte & 0x01);
		byte >>= 1;
	}	
}

void ds18b20_write2(uchar byte){
	uchar i = 0;
	for(i=8;i>0;i--){
		ds18b20_write_bit2(byte & 0x01);
		byte >>= 1;
	}	
}

uchar ds18b20_read_bit1(){
	uchar bt;
	DQ1 = 0;				
	delay(1);			
	DQ1 = 1;					
	if(DQ1)			
		bt = 0x01;		
	delay(11);

	return bt;
}

uchar ds18b20_read_bit2(){
	uchar bt;
	DQ2 = 0;				
	delay(1);			
	DQ2 = 1;					
	if(DQ2)			
		bt = 0x01;		
	delay(11);

	return bt;
}

uchar ds18b20_read_2bits1(){
	uchar i, b2;
	for(i=2;i>0;i--){
		DQ1 = 0;			
		delay(1);		
		DQ1 = 1;			
		b2 <<= 1;		
		if(DQ1)			
			b2 |= 0x10;		
		delay(11);	
	}


	return b2;
}

uchar ds18b20_read_2bits2(){
	uchar i, b2;
	for(i=2;i>0;i--){
		DQ2 = 0;			
		delay(1);		
		DQ2 = 1;			
		b2 <<= 1;		
		if(DQ2)			
			b2 |= 0x10;		
		delay(11);	
	}

	return b2;
}

uchar ds18b20_read1(){
	uchar i, byte = 0;
	for(i=8;i>0;i--){
		DQ1 = 0;			
		delay(1);		
		DQ1 = 1;			
		byte >>= 1;		
		if(DQ1)			
			byte |= 0x80;		
		delay(11);
	}
	return byte;	
}

uchar ds18b20_read2(){
	uchar i, byte = 0;
	for(i=8;i>0;i--){
		DQ2 = 0;			
		delay(1);		
		DQ2 = 1;			
		byte >>= 1;		
		if(DQ2)			
			byte |= 0x80;		
		delay(11);
	}
	return byte;	
}

uchar ds18b20_read_temp1(){
	uchar templ, temph, tt;
	uint t;
	ds18b20_init1();		   
	ds18b20_write1(0XCC);	   
	ds18b20_write1(0x44);

	ds18b20_init1();		 
	ds18b20_write1(0xcc);	  
	ds18b20_write1(0xbe);
		 
	templ=ds18b20_read1();	 
	temph=ds18b20_read1();	  
	t = temph;
	t <<= 8;
	t = t | templ;
	tt = t * 0.0625;
			  
	return tt;			   
}

uchar ds18b20_read_temp2(){
	uchar templ, temph, tt;
	uint t;
	ds18b20_init2();		   
	ds18b20_write2(0XCC);	   
	ds18b20_write2(0x44);

	ds18b20_init2();		 
	ds18b20_write2(0xcc);	  
	ds18b20_write2(0xbe);
		 
	templ=ds18b20_read2();	 
	temph=ds18b20_read2();	  
	t = temph;
	t <<= 8;
	t = t | templ;
	tt = t * 0.0625;
			  
	return tt;			   
}
