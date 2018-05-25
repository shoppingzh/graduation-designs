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
* TCK�ȵ�ż ��ȡ�¶�
*/
uint tck_read_temp1(){
	uchar i;
	uint temp;

	CS1 = 1;			//�����¶�ת��
	_nop_();
	_nop_();
	CS1 = 0;			//ֹͣ�¶�ת������ʼ��ȡ
	_nop_();
	_nop_();
	for(i=0;i<16;i++){
		temp <<= 1;
		SCK1 = 1;
		_nop_();
		SCK1 = 0;	//�õ��½��أ�������ʱ���ȡSO
		_nop_();
		if(SO1)
			temp |= 0x01;
	}

	temp <<= 1;		//ȥ����0��1��2��15λ
	temp >>= 4;

	return (temp >> 2) - COLD_TEMPERATURE + 1;		//��tempת��Ϊ�����¶Ȳ���ȥ����¶�
}

/**
* TCK�ȵ�ż ��ȡ�¶�
*/
uint tck_read_temp2(){
	uchar i;
	uint temp;

	CS2 = 1;			//�����¶�ת��
	_nop_();
	_nop_();
	CS2 = 0;			//ֹͣ�¶�ת������ʼ��ȡ
	_nop_();
	_nop_();
	for(i=0;i<16;i++){
		temp <<= 1;
		SCK2 = 1;
		_nop_();
		SCK2 = 0;	//�õ��½��أ�������ʱ���ȡSO
		_nop_();
		if(SO2)
			temp |= 0x01;
	}

	temp <<= 1;		//ȥ����0��1��2��15λ
	temp >>= 4;

	return (temp >> 2) - COLD_TEMPERATURE + 1;		//��tempת��Ϊ�����¶Ȳ���ȥ����¶�
}