#ifndef _DS18B20_H_
#define _DS18B20_H_

#define uchar unsigned char
#define uint unsigned int
#define MAX_NUM 4

//DS18B20 ROM±àÂë£º64Î»
typedef struct{
	uchar ds18b20_code;
	uchar sn_1;
	uchar sn_2;
	uchar sn_3;
	uchar sn_4;
	uchar sn_5;
	uchar sn_6;
	uchar crc;
}ds18b20_rom_code;

extern uchar temper_readtemp1();
extern uchar temper_readtemp2();
extern uchar temper_readtemp3();
extern uchar temper_readtemp4();

#endif