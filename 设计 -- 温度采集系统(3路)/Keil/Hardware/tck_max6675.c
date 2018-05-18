#include "tck_max6675.h"
#include "reg51.h"
#include "intrins.h"

sbit SO = P1^0;
sbit SCK = P1^1;
sbit CS = P1^2;		//�͵�ƽ��Ч

/**
* TCK�ȵ�ż ��ȡ�¶�
*/
uint tck_read_temp(){
	uchar i;
	uint temp;

	CS = 1;			//�����¶�ת��
	_nop_();
	_nop_();
	CS = 0;			//ֹͣ�¶�ת������ʼ��ȡ
	_nop_();
	_nop_();
	for(i=0;i<16;i++){
		temp <<= 1;
		SCK = 1;
		_nop_();
		SCK = 0;	//�õ��½��أ�������ʱ���ȡSO
		_nop_();
		if(SO)
			temp |= 0x01;
	}

	temp <<= 1;		//ȥ����0��1��2��15λ
	temp >>= 4;

	return (temp >> 2) - COLD_TEMPERATURE + 1;		//��tempת��Ϊ�����¶Ȳ���ȥ����¶�
}