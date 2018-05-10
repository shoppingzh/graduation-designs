#include <reg52.h>//包含头文件
#include "key.h"

#define uchar unsigned char
#define uint unsigned int
#define PORT P2
//unsigned char const dofly[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,
//                    0x77,0x7c,0x39,0x5e,0x79,0x71};//0-F，数码管来显示按下键的值。


//void main()
//{
//	uchar key;
//	P2=0x00;//1数码管亮 按相应的按键，会显示按键上的字符
//	while(1)
//	{
//		key=keyscan();//调用键盘扫描，
//		switch(key)
//		{
//			case 0x7e:P0=dofly[0];break;//0 按下相应的键显示相对应的码值 原理就是高四位一列低四位一列的组
//			//合。0111    1110 7e    0表示按键后为0，1表示没有按键按下的。即P3.7与P3.1连接为低电平，为S1键
//			//其他类推。
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


static void delay(uint i)//延时函数
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



int keyscan(void)//键盘扫描函数，使用行列反转扫描法 比如：行为低电位，列为高四位
{
	uchar cord_h,cord_l;	//行列值
	PORT=0x0f;            //行线输出全为0
	//cord_h=PORT&0x0f;     //读入列线值


	if((PORT&0x0f)!=0x0f)    //先检测有无按键按下
	{
		//delay(100);        //去抖
		if((PORT&0x0f)!=0x0f)
		{

		    cord_h=PORT&0x0f; //读入列线值
		    PORT=cord_h|0xf0; //输出当前列线值
		    cord_l=PORT&0xf0; //读入行线值

			while( ((PORT&0x0f) == cord_h) && ((PORT&0xf0) == cord_l) );
			return convert(cord_h+cord_l);
		    //return(cord_h+cord_l);//键盘最后组合码值
	   	}
	}
	
	return convert(0xff);     //返回该值
	//return 0xff;
}


