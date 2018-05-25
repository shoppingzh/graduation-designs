#ifndef _UART_H_
#define _UART_H_

#define uchar unsigned char

extern void uart_init();
extern void uart_send(uchar dat);
extern uchar uart_receive();
extern void uart_received(uchar dat);

#endif