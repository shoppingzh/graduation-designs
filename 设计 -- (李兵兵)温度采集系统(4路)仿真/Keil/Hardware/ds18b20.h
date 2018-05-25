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

extern void ds18b20_init1();
extern void ds18b20_write_bit1(uchar b);
extern void ds18b20_write1(uchar byte);
extern uchar ds18b20_read_bit1();
extern uchar ds18b20_read_2bits1();
extern uchar ds18b20_read1();
extern uchar ds18b20_read_temp1();

extern void ds18b20_init2();
extern void ds18b20_write_bit2(uchar b);
extern void ds18b20_write2(uchar byte);
extern uchar ds18b20_read_bit2();
extern uchar ds18b20_read_2bits2();
extern uchar ds18b20_read2();
extern uchar ds18b20_read_temp2();


#endif