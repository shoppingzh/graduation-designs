#include "tck_max6675.h"
#include "reg51.h"
#include "intrins.h"

sbit SO = P1^0;
sbit SCK = P1^1;
sbit CS = P1^2;		//低电平有效

/**
* TCK热电偶 读取温度
*/
uint tck_read_temp(){
	uchar i;
	uint temp;

	CS = 1;			//启动温度转换
	_nop_();
	_nop_();
	CS = 0;			//停止温度转换，开始读取
	_nop_();
	_nop_();
	for(i=0;i<16;i++){
		temp <<= 1;
		SCK = 1;
		_nop_();
		SCK = 0;	//得到下降沿，短暂延时后读取SO
		_nop_();
		if(SO)
			temp |= 0x01;
	}

	temp <<= 1;		//去除第0、1、2、15位
	temp >>= 4;

	return (temp >> 2) - COLD_TEMPERATURE + 1;		//将temp转换为正常温度并减去冷端温度
}