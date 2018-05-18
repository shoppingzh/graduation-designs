#include "reg52.h"
#include "lcd1602.h"

sbit relay = P3^0;

void main(){
	lcd_simple_init();

	lcd_display_string(1, 1, "Weight: 0");
	lcd_display_string(2, 1, "Overweight: no");
	relay = 0;

	while(1);
}
