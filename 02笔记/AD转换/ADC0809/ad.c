#include <reg52.h>
sbit	EOC=P1^0;
sbit	START=P1^1;
sbit	con=P1^2;
main()
{
	unsigned char	i;
	for(i=0;i<2;i++);  //等待一下，有的电脑仿真时比较慢，仿真时可能需要等待复位状态
	while(1)
	{
	if(!EOC)//如果EOC为低电屏，则产生一个脉冲，这个脉冲的下降沿用于启动AD转换
	{
		START=1;
		START=0;
	}
	while(!EOC);//等待AD转换结束
	START=1;	//转换结束后，再产生一个脉冲，这个脉冲的下降沿用于将EOC置为低电屏，为下一次转换作准备
	START=0;
	}

}