#include "reg51.h"
#include "lcd1602.h"
#include "stdio.h"
#include "intrins.h"
#include "fpm10a.h"
#include "uart_syn.h"

sbit key = P3^5;
sbit led = P2^6;

void delay1s(void)   //Îó²î 0us
{
    unsigned char a,b,c;
    for(c=167;c>0;c--)
        for(b=171;b>0;b--)
            for(a=16;a>0;a--);
    _nop_();  //if Keil,require use intrins.h
}					

void main(){
	uint num;
	//Init
	lcd_simple_init();
	fpm_init();

	lcd_display_string(1, 1, "Hello");
	
		
	if(fpm_auto_search(0, 100) >= 50){
		lcd_display_string(1, 1, "Have the finger");		
	}else{
		num = fpm_template_num();
		fpm_add_template(38);
		if(fpm_template_num() == num+1){
			lcd_display_string(2, 1, "Success!");
		}
	}

//	score = fpm_auto_search(0, 50);
//	sprintf(str, "Score: %d", (int)score);
//	lcd_display_string(1, 1, str);

//	lcd_display_string(1, 1, "Touch finger");
//	while(fpm_genimg() != 0x00);
//	if(fpm_genimg() == 0x00){
//		fpm_img2char(1);
//	}
//	
//	lcd_clear();
//	lcd_display_string(1, 1, "Touch again");
//	while(fpm_genimg() != 0x00);
//	fpm_genimg();

	
//
//	temp = fpm_autoregister(16);
//	sprintf(str, "%02x-----", (int)temp);
//	lcd_clear();
//	lcd_display_string(1, 1, str);

//	temp = fpm_add_template(i++);
//	sprintf(str, "%02x-----", (int)temp);
//	lcd_clear();
//	lcd_display_string(1, 1, str);

	
//	fpm_add_template(2);
//	delay1s();

	
	while(1){
		

		if(!key){
			led = ~led;
			while(!key);
		}
	}
		
}
