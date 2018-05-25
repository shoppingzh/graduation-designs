#include "tck_max6675.h"
#include "reg51.h"
#include "intrins.h"

sbit SO1 = P1^0;
sbit SCK1 = P1^1;
sbit CS1 = P1^2;

sbit SO2 = P1^3;
sbit SCK2 = P1^4;
sbit CS2 = P1^5;

/**
* TCK热电偶 读取温度
*/
uint tck_read_temp1(){
	uchar i;
	uint temp;

	CS1 = 1;			//启动温度转换
	_nop_();
	_nop_();
	CS1 = 0;			//停止温度转换，开始读取
	_nop_();
	_nop_();
	for(i=0;i<16;i++){
		temp <<= 1;
		SCK1 = 1;
		_nop_();
		SCK1 = 0;	//得到下降沿，短暂延时后读取SO
		_nop_();
		if(SO1)
			temp |= 0x01;
	}

	temp <<= 1;		//去除第0、1、2、15位
	temp >>= 4;

	return (temp >> 2) - COLD_TEMPERATURE + 1;		//将temp转换为正常温度并减去冷端温度
}

/**
* TCK热电偶 读取温度
*/
uint tck_read_temp2(){
	uchar i;
	uint temp;

	CS2 = 1;			//启动温度转换
	_nop_();
	_nop_();
	CS2 = 0;			//停止温度转换，开始读取
	_nop_();
	_nop_();
	for(i=0;i<16;i++){
		temp <<= 1;
		SCK2 = 1;
		_nop_();
		SCK2 = 0;	//得到下降沿，短暂延时后读取SO
		_nop_();
		if(SO2)
			temp |= 0x01;
	}

	temp <<= 1;		//去除第0、1、2、15位
	temp >>= 4;

	return (temp >> 2) - COLD_TEMPERATURE + 1;		//将temp转换为正常温度并减去冷端温度
}