#include "reg51.h"
#include "lcd1602.h"

void main(){
	lcd_simple_init();
	//lcd_init(ENABLE, DISABLE);
	
	lcd_display_string(1, 1, "Hello, world!");
	
	while(1);		
}
