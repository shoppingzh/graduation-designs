#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int

#include "uart.h"
#include "uart_support.h"

void analyse(uchar packet[], uchar size);

void main(void){
	uart_init();
	while(1);
}

void receive_packet(uchar packet[], uchar size){
	send_string(packet);
	analyse(packet, size);	
}

void analyse(uchar packet[], uchar size){
	if(packet[2] == 0x01){
		P1 = packet[3];							 
		send_string(", CNM...");
	}
}