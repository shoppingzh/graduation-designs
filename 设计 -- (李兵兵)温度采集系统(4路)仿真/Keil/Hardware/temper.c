#include "temper.h"
#include "reg51.h"
#include "intrins.h"
#include "uart.h"

sbit DQ1 = P2^0;
sbit DQ2 = P2^1;
sbit DQ3 = P2^2;
sbit DQ4 = P2^3;

/**
* 短暂延时
*/
static void delay(uchar i){
	do{
		_nop_();
		_nop_();
		_nop_();
		i--;
	}while(i);
}

///////////////////4路初始化

static void d1_init(){
	uchar rst;
	DQ1 = 1;		  
	delay(10);	  
	DQ1 = 0;		 
	delay(120);	  
	DQ1 = 1;		 
	delay(16);
	rst = DQ1;	 		
	delay(80);	
	DQ1 = 1;
	P0 = rst;
}

static void d2_init(){
	uchar rst = 0;
   	DQ2 = 1;		  
	delay(10);	  
	DQ2 = 0;		 
	delay(120);	  
	DQ2 = 1;		 
	delay(16);
	rst = DQ2;	 		
	delay(80);	
	DQ2 = 1;
	P0 = rst;
}

static void d3_init(){
	uchar rst = 0;
	DQ3 = 1;		  
	delay(10);	  
	DQ3 = 0;		 
	delay(120);	  
	DQ3 = 1;		 
	delay(16);
	rst = DQ3;	 		
	delay(80);	
	DQ3 = 1;
	P0 = rst;
}

static void d4_init(){
	uchar rst = 0;
	DQ4 = 1;		  
	delay(10);	  
	DQ4 = 0;		 
	delay(120);	  
	DQ4 = 1;		 
	delay(16);
	rst = DQ4;	 		
	delay(80);	
	DQ4 = 1;
	P0 = rst;	
}


/////////////////4路写数据

static void d1_write(uchar byte){
	uchar i = 0;
	for(i=8;i>0;i--){
		DQ1 = 0;
		DQ1 = byte & 0x01;			
		delay(12);				 
		DQ1 = 1;
		delay(5);
		byte >>= 1;
	}	
}

static void d2_write(uchar byte){
	uchar i = 0;
	for(i=8;i>0;i--){
		DQ2 = 0;
		DQ2 = byte & 0x01;			
		delay(12);				 
		DQ2 = 1;
		delay(5);
		byte >>= 1;
	}
}

static void d3_write(uchar byte){
	uchar i = 0;
	for(i=8;i>0;i--){
		DQ3 = 0;
		DQ3 = byte & 0x01;			
		delay(12);				 
		DQ3 = 1;
		delay(5);
		byte >>= 1;
	}
}

static void d4_write(uchar byte){
	uchar i = 0;
	for(i=8;i>0;i--){
		DQ4 = 0;
		DQ4 = byte & 0x01;			
		delay(12);				 
		DQ4 = 1;
		delay(5);
		byte >>= 1;
	}
}

//////////////4路读数据

static uchar d1_read(){
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

static uchar d2_read(){
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

static uchar d3_read(){
	uchar i, byte = 0;
	for(i=8;i>0;i--){
		DQ3 = 0;			
		delay(1);		
		DQ3 = 1;			
		byte >>= 1;		
		if(DQ3)			
			byte |= 0x80;		
		delay(11);
	}
	return byte;
}

static uchar d4_read(){
	uchar i, byte = 0;
	for(i=8;i>0;i--){
		DQ4 = 0;			
		delay(1);		
		DQ4 = 1;			
		byte >>= 1;		
		if(DQ4)			
			byte |= 0x80;		
		delay(11);
	}
	return byte;
}

/******************************** API *****************************/

uchar temper_readtemp1(){
	uchar templ, temph, tt;
	uint t;
	d1_init();		   
	d1_write(0xcc);	   
	d1_write(0x44);

	d1_init();		 
	d1_write(0xcc);	  
	d1_write(0xbe);
		 
	templ = d1_read();	 
	temph = d1_read();	  
	t = temph;
	t <<= 8;
	t = t | templ;
	tt = t * 0.0625;
			  
	return tt;
}

uchar temper_readtemp2(){
	uchar templ, temph, tt;
	uint t;
	d2_init();		   
	d2_write(0xcc);	   
	d2_write(0x44);

	d2_init();		 
	d2_write(0xcc);	  
	d2_write(0xbe);
		 
	templ = d2_read();	 
	temph = d2_read();	  
	t = temph;
	t <<= 8;
	t = t | templ;
	tt = t * 0.0625;
			  
	return tt;
}

uchar temper_readtemp3(){
 	uchar templ, temph, tt;
	uint t;
	d3_init();		   
	d3_write(0xcc);	   
	d3_write(0x44);

	d3_init();		 
	d3_write(0xcc);	  
	d3_write(0xbe);
		 
	templ = d3_read();	 
	temph = d3_read();	  
	t = temph;
	t <<= 8;
	t = t | templ;
	tt = t * 0.0625;
			  
	return tt;
}

uchar temper_readtemp4(){
	uchar templ, temph, tt;
	uint t;
	d4_init();		   
	d4_write(0xcc);	   
	d4_write(0x44);

	d4_init();		 
	d4_write(0xcc);	  
	d4_write(0xbe);
		 
	templ = d4_read();	 
	temph = d4_read();	  
	t = temph;
	t <<= 8;
	t = t | templ;
	tt = t * 0.0625;
			  
	return tt;
}
