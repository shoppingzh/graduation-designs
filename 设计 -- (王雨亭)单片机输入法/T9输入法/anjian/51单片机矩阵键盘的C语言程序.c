#include <reg52.h>//����ͷ�ļ�
#define uchar unsigned char
#define uint unsigned int
unsigned char const dofly[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,
                    0x77,0x7c,0x39,0x5e,0x79,0x71};//0-F�����������ʾ���¼���ֵ��

uchar keyscan(void);            //��Ҫ�ľ������ɨ�躯����
void delay(uint i);
void main()
{
uchar key;
P2=0x00;//1������� ����Ӧ�İ���������ʾ�����ϵ��ַ�
while(1)
{
key=keyscan();//���ü���ɨ�裬
switch(key)
{
case 0x7e:P0=dofly[0];break;//0 ������Ӧ�ļ���ʾ���Ӧ����ֵ ԭ����Ǹ���λһ�е���λһ�е���
//�ϡ�0111    1110 7e    0��ʾ������Ϊ0��1��ʾû�а������µġ���P3.7��P3.1����Ϊ�͵�ƽ��ΪS1��
//�������ơ�
case 0x7d:P0=dofly[1];break;//1
case 0x7b:P0=dofly[2];break;//2
case 0x77:P0=dofly[3];break;//3
case 0xbe:P0=dofly[4];break;//4
case 0xbd:P0=dofly[5];break;//5
case 0xbb:P0=dofly[6];break;//6
case 0xb7:P0=dofly[7];break;//7
case 0xde:P0=dofly[8];break;//8
case 0xdd:P0=dofly[9];break;//9
case 0xdb:P0=dofly[10];break;//a
case 0xd7:P0=dofly[11];break;//b
case 0xee:P0=dofly[12];break;//c
case 0xed:P0=dofly[13];break;//d
case 0xeb:P0=dofly[14];break;//e
case 0xe7:P0=dofly[15];break;//f
}
}
}
uchar keyscan(void)//����ɨ�躯����ʹ�����з�תɨ�跨 ���磺��Ϊ�͵�λ����Ϊ����λ
{
uchar cord_h,cord_l;//����ֵ
P3=0x0f;            //�������ȫΪ0
cord_h=P3&0x0f;     //��������ֵ
if(cord_h!=0x0f)    //�ȼ�����ް�������
{
delay(100);        //ȥ��
if(cord_h!=0x0f)
{
    cord_h=P3&0x0f; //��������ֵ
    P3=cord_h|0xf0; //�����ǰ����ֵ
    cord_l=P3&0xf0; //��������ֵ
    return(cord_h+cord_l);//������������ֵ
   }
}return(0xff);     //���ظ�ֵ
}
void delay(uint i)//��ʱ����
{
while(i--);
}����Ϊ51��Ƭ���������ɨ����ʾ����
