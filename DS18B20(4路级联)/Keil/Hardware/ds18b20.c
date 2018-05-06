#include "ds18b20.h"
#include "reg51.h"
#include "intrins.h"
#include "uart.h"

sbit DQ = P2^0;

/**
* 短暂延时
*/
void delay(uchar i){
	do{
		_nop_();
		_nop_();
		_nop_();
		i--;
	}while(i);
}

/**
* DS18B20 初始化
* 返回0，初始化成功；否则， 初始化失败
*/
uchar ds18b20_init(){
	uchar rst = 0;
	DQ = 1;		  
	delay(10);	  
	DQ = 0;		 
	delay(120);	  
	DQ = 1;		 
	delay(16);	 
	rst = DQ;		
	delay(80);	
	DQ = 1;
	
	return rst;		
}

/*
* DS18B20 写一位数据
*/
void ds18b20_write_bit(uchar b){
	DQ = 0;
	DQ = b&0x01;			
	delay(12);				 
	DQ = 1;
	delay(5);	
}

/*
* DS18B20 写一个字节的数据
*/
void ds18b20_write(uchar byte){
	uchar i = 0;
	for(i=8;i>0;i--){
		ds18b20_write_bit(byte & 0x01);
		byte >>= 1;
	}	
}

/*
* DS18B20 读取一位数据
*/
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

/**
* DS18B20 读取两位数据
*/
uchar ds18b20_read_2bits(){
	uchar i, b2;
	for(i=2;i>0;i--){
		DQ = 0;			
		delay(1);		
		DQ = 1;			
		b2 <<= 1;		
		if(DQ)			
			b2 |= 0x01;		
		delay(10);	
	}

	return b2;
}

/**
* DS18B20 读取一个字节的数据
*/
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

/**
* DS18B20 当总线上挂载1个DS18B20时，读取这个DS18B20的温度值
*/
uchar ds18b20_read_temp1(){
	uchar templ, temph, tt;
	uint t;
	ds18b20_init();		   
	ds18b20_write(0xcc);	   
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

/**
* DS18B20 当总线上挂载1个DS18B20时，读取这个DS18B20的64位ROM
*/
uchar* ds18b20_read_rom(){
	uchar i, rom[8];
	ds18b20_init();
	ds18b20_write(0x33);

	for(i=0;i<8;i++){
		rom[i] = ds18b20_read();
	}

	return rom;
}

/**
* DS18B20 当总线上挂载多个DS18B20时，搜索这些DS18B20的ROM并存储
* @param ids 所有DS18B20的ROM存储数组
* @param num DS18B20的个数
*/
void ds18b20_search_rom(uchar (*ids)[8], uchar* num){
	uchar i, j;
	uchar k;
	uchar ss[64];

	uchar cfl;
	uchar stack[MAX_NUM - 1];
	uchar p = 0;

	do{
		ds18b20_init();
		ds18b20_write(0xf0);

		for(i=0;i<8;i++){
			uchar s = 0;
			for(j=0;j<8;j++){
				k = ds18b20_read_2bits();
				k &= 0x03;
				s >>= 1;
				if(k == 0x01){
					ds18b20_write_bit(0);
					ss[i*8+j] = 0;
				}else if(k == 0x02){
					s |= 0x80;
					ds18b20_write_bit(1);
					ss[i*8+j] = 1;		
				}else if(k == 0x00){
					cfl = i * 8 + j + 1;
					if(cfl > stack[p]){
						ds18b20_write_bit(0);
						ss[i*8+j] = 0;
						stack[++p] = cfl;
					}else if(cfl < stack[p]){
						s |= ((ss[8*i+j] & 0x01) << 7);
						ds18b20_write_bit(ss[i*8+j]);		
					}else if(cfl == stack[p]){
						s |= 0x80;
						ds18b20_write_bit(1);
						ss[8*i+j] = 1;
						p -= 1;						
					}	
				}else{
					//do nothing
				}
			}
			ids[*num][i] = s; 			
		}
		(*num)++;
	}while((stack[p] != 0) && (*num < MAX_NUM));
}
