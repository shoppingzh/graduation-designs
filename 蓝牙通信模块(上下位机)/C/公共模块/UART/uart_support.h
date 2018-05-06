#ifndef _UART_PACKET_H
#define _UART_PACKET_H

#include <string.h>

#define uchar unsigned char
#define PACKET_SIZE 6

extern uchar packet[PACKET_SIZE];
extern uchar pos;

void receive_byte(uchar rec_data);
void receive_packet(uchar packet[], uchar packet_size);

#endif
