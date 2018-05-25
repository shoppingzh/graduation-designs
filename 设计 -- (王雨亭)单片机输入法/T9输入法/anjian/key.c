#include <reg52.h>//����ͷ�ļ�
#include "key.h"

#define uchar unsigned char
#define uint unsigned int
#define PORT P2
//unsigned char const dofly[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,
//                    0x77,0x7c,0x39,0x5e,0x79,0x71};//0-F�����������ʾ���¼���ֵ��


//void main()
//{
//	uchar key;
//	P2=0x00;//1������� ����Ӧ�İ���������ʾ�����ϵ��ַ�
//	while(1)
//	{
//		key=keyscan();//���ü���ɨ�裬
//		switch(key)
//		{
//			case 0x7e:P0=dofly[0];break;//0 ������Ӧ�ļ���ʾ���Ӧ����ֵ ԭ����Ǹ���λһ�е���λһ�е���
//			//�ϡ�0111    1110 7e    0��ʾ������Ϊ0��1��ʾû�а������µġ���P3.7��P3.1����Ϊ�͵�ƽ��ΪS1��
//			//�������ơ�
//			case 0x7d:P0=dofly[1];break;//1
//			case 0x7b:P0=dofly[2];break;//2
//			case 0x77:P0=dofly[3];break;//3
//			case 0xbe:P0=dofly[4];break;//4
//			case 0xbd:P0=dofly[5];break;//5
//			case 0xbb:P0=dofly[6];break;//6
//			case 0xb7:P0=dofly[7];break;//7
//			case 0xde:P0=dofly[8];break;//8
//			case 0xdd:P0=dofly[9];break;//9
//			case 0xdb:P0=dofly[10];break;//a
//			case 0xd7:P0=dofly[11];break;//b
//			case 0xee:P0=dofly[12];break;//c
//			case 0xed:P0=dofly[13];break;//d
//			case 0xeb:P0=dofly[14];break;//e
//			case 0xe7:P0=dofly[15];break;//f
//		}
//	}
//}


static void delay(uint i)//��ʱ����
{
	while(i--);
}

static int convert(key){
	int v;
	switch(key)
	{
		case 0xd7:
			v = 0;
			break;
		case 0xee:
			v = 1;
			break;
		case 0xde:
			v = 2;
			break;
		case 0xbe:
			v = 3;
			break;
		case 0xed:
			v = 4;
			break;
		case 0xdd:
			v = 5;
			break;
		case 0xbd:
			v = 6;
			break;
		case 0xeb:
			v = 7;
			break;//7
		case 0xdb:
			v = 8;
			break;//8
		case 0xbb:
			v = 9;
			break;//9
		case 0xe7:
			v = 10;
			break;
		case 0xb7:
			v = 11;
			break;
		//* #
//		case 0xdb:P0=dofly[10];break;//a
//		case 0xd7:P0=dofly[11];break;//b
//		case 0xee:P0=dofly[12];break;//c
//		case 0xed:P0=dofly[13];break;//d
//		case 0xeb:P0=dofly[14];break;//e
//		case 0xe7:P0=dofly[15];break;//f
		case 0xff:
			v = -1;
			break;
		default:
			v = -1;
			break;
	}			 

	return v;
}



int keyscan(void)//����ɨ�躯����ʹ�����з�תɨ�跨 ���磺��Ϊ�͵�λ����Ϊ����λ
{
	uchar cord_h,cord_l;	//����ֵ
	PORT=0x0f;            //�������ȫΪ0
	//cord_h=PORT&0x0f;     //��������ֵ


	if((PORT&0x0f)!=0x0f)    //�ȼ�����ް�������
	{
		//delay(100);        //ȥ��
		if((PORT&0x0f)!=0x0f)
		{

		    cord_h=PORT&0x0f; //��������ֵ
		    PORT=cord_h|0xf0; //�����ǰ����ֵ
		    cord_l=PORT&0xf0; //��������ֵ

			while( ((PORT&0x0f) == cord_h) && ((PORT&0xf0) == cord_l) );
			return convert(cord_h+cord_l);
		    //return(cord_h+cord_l);//������������ֵ
	   	}
	}
	
	return convert(0xff);     //���ظ�ֵ
	//return 0xff;
}


