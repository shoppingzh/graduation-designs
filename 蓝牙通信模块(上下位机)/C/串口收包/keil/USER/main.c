#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int

#include "uart.h"
#include "uart_support.h"

void on_receive(uchar rec_data);

void main(void){
	uart_init();
	while(1);	
}

void send(uchar send_data){
	SBUF = send_data;
	while(!TI);
	TI = 0;
}

void receive_packet(uchar packet[], uchar packet_size){
	uchar i;
	for(i=0;i<packet_size;i++){
		send(packet[i]);
	}	
}

