#include <reg52.h>
sbit	EOC=P1^0;
sbit	START=P1^1;
sbit	con=P1^2;
main()
{
	unsigned char	i;
	for(i=0;i<2;i++);  //�ȴ�һ�£��еĵ��Է���ʱ�Ƚ���������ʱ������Ҫ�ȴ���λ״̬
	while(1)
	{
	if(!EOC)//���EOCΪ�͵����������һ�����壬���������½�����������ADת��
	{
		START=1;
		START=0;
	}
	while(!EOC);//�ȴ�ADת������
	START=1;	//ת���������ٲ���һ�����壬���������½������ڽ�EOC��Ϊ�͵�����Ϊ��һ��ת����׼��
	START=0;
	}

}