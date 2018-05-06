#include "reg51.h"
#include "lcd12864.h"
#include "intrins.h"

#define uchar unsigned char

void delay1s(void)   //ŒÛ≤Ó 0us
{
    unsigned char a,b,c;
    for(c=167;c>0;c--)
        for(b=171;b>0;b--)
            for(a=16;a>0;a--);
    _nop_();  //if Keil,require use intrins.h
}


void main(){
	lcd_init();

	lcd_display_string(1, 1, "ª∂”≠ π”√£°");
   	


	while(1){
		//
	}		
}
