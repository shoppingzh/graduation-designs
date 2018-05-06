#include <reg51.h>
#include "ds18b20.h"
#include "uart.h"

uchar num = 0;		//DS18B20������
uchar xdata ids[MAX_NUM][8];

void delay(){
	uchar i, j, k;
	for(i=0;i<10;i++)
		for(j=0;j<100;j++)
			for(k=0;k<200;k++);
}

void main(){

	uchar i, j;
	//uchar* rom;	

	uart_init();

	//��ȡROM
	//rom = ds18b20_read_rom();
	//for(i=0;i<8;i++){
	//	uart_send(rom[i]);	
	//}
	//uart_send(num);

	//����ROM
	delay();
	ds18b20_search_rom(ids, &num);
	delay();
	uart_send(num);

	for(i=0;i<num;i++){
		for(j=0;j<8;j++){
			uart_send(ids[i][j]);
		}	
	}
	
	while(1){
		//uart_send(ds18b20_read_temp1());
		//delay();
	}		
}
