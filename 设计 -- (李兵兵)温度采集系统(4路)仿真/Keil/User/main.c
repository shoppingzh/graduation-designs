#include "reg52.h"
#include "ds18b20.h"
#include "adc.h"
#include "tck_max6675.h"
#include "uart.h"

uchar r1, r2, r3, r4;

void main(){

	uart_init();
	while(1){
	
	}

}

void uart_received(uchar cmd){
	switch(cmd){
		case 0x01:
			uart_send(ds18b20_read_temp1());
			break;
		case 0x02:
			uart_send(ds18b20_read_temp2());
			break;
		case 0x03:
			uart_send(tck_read_temp1());
			break;
		case 0x04:
			uart_send(tck_read_temp2());
			break;
		default:
			break;
	}
}


