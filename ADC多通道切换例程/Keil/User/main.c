#include "reg51.h"
#include "adc.h"

sbit ADDA = P2^4;

void delay500ms(void)   //Îó²î 0us
{
    unsigned char a,b,c;
    for(c=23;c>0;c--)
        for(b=152;b>0;b--)
            for(a=70;a>0;a--);
}

void delay5ms(void)   //Îó²î 0us
{
    unsigned char a,b;
    for(b=19;b>0;b--)
        for(a=130;a>0;a--);
}


void main(){
	adc_init();
	while(1){
		ADDA = ~ADDA;
		//delay500ms();
		delay5ms();
		if(!ADDA){
			P0 = adc_transform();
		}else{
			P3 = adc_transform();
		}
		
	}
}
