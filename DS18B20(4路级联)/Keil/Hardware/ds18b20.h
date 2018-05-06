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

extern uchar ds18b20_init();
extern void ds18b20_write_bit(uchar b);
extern void ds18b20_write(uchar byte);
extern uchar ds18b20_read_bit();
extern uchar ds18b20_read_2bits();
extern uchar ds18b20_read();
extern uchar ds18b20_read_temp1();
extern uchar* ds18b20_read_rom();
extern void ds18b20_search_rom(uchar (*ids)[8], uchar* num);

#endif