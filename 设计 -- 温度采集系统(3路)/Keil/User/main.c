#include "reg52.h"
#include "ds18b20.h"
#include "adc.h"
#include "tck_max6675.h"
#include "lcd1602.h"
#include "stdio.h"

void display(uint t1, uint t2, uint t3, uint t4);

uchar r1, r2, r3, r4;

void main(){

	uchar t1, t2, t3, t4;
	ds18b20_init();
	lcd_simple_init();



	while(1){
		t1 = ds18b20_read_temp1();
		t2 = tck_read_temp();

		display(t1, t2, t3, t4);

		r1 = t1;
		r2 = t2;
	}
}

//œ‘ æ
void display(uint t1, uint t2, uint t3, uint t4){
	char arr1[5], arr2[5], arr3[5], arr4[5];
	if(t1 == r1 && t2 == r2 && t3 == r3 && t4 == r4)
		return;

	lcd_clear();
   	lcd_display_string(1, 1, "T1: ");
	lcd_display_string(1, 8, "T2: ");
	lcd_display_string(2, 1, "T3: ");
	lcd_display_string(2, 8, "T4: ");

	sprintf(arr1, "%d", (int)r1);
	sprintf(arr2, "%d", (int)r2);
	sprintf(arr3, "%d", (int)r3);
	sprintf(arr4, "%d", (int)r4);
	lcd_display_string(1, 4, arr1);
	lcd_display_string(1, 11, arr2);
	lcd_display_string(2, 4, arr3);
	lcd_display_string(2, 11, arr4);
}
