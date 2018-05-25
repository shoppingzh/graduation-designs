#ifndef _UART_SYN_H_
#define _UART_SYN_H_

#ifndef uchar
	#define uchar unsigned char
#endif

extern void uart_init();
extern void uart_send(uchar dat);
extern uchar uart_receive();

#endif