#include <REGX51.H>
#include "intrins.h"
#define uchar unsigned char

sbit pwm = P2^0;
sbit key = P3^5;
bit flag;


//Ë³Ê±Õë90
void delay2ms(void)   //Îó²î -0.217013888889us
{
    unsigned char a,b,c;
    for(c=2;c>0;c--)
        for(b=4;b>0;b--)
            for(a=113;a>0;a--);
}

void delay18ms(void)   //Îó²î -0.868055555558us
{
    unsigned char a,b;
    for(b=161;b>0;b--)
        for(a=50;a>0;a--);
}

//ÄæÊ±Õë90
void delay19ms(void)   //Îó²î -0.43402777778us
{
    unsigned char a,b;
    for(b=45;b>0;b--)
        for(a=193;a>0;a--);
}
void delay1ms(void)   //Îó²î -0.651041666667us
{
    unsigned char a,b;
    for(b=4;b>0;b--)
        for(a=113;a>0;a--);
}

void se_up(){
	uchar i;
	for(i=0;i<50;i++){
	   	pwm = 1;
	   	delay1ms();
		pwm = 0;
		delay19ms();
	}	
}

void se_down(){
	uchar i;
	for(i=0;i<50;i++){
	   	pwm = 1;
	   	delay2ms();
		pwm = 0;
		delay18ms();
	}
	
}

void delay200ms(void)   //Îó²î -0.000000000058us
{
    unsigned char a,b,c;
    for(c=193;c>0;c--)
        for(b=136;b>0;b--)
            for(a=2;a>0;a--);
}






void main(){
	
	while(1){
		//delay200ms();
		se_up();
		//delay200ms();
		se_down();
		
		/*if(!key){
			flag = !flag;			
			while(!key);
		}
	   	if(flag){
			se_up();
		}else{
			se_down();
		}*/

	}
}


