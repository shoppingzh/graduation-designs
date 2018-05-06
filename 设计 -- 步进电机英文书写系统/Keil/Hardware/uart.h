#ifndef _UART_H_
#define _UART_H_

#ifndef uchar
	#define uchar unsigned char
#endif
#ifndef uint
	#define uint unsigned int
#endif
#ifndef ulong
	#define ulong unsigned long
#endif

extern void uart_init();
extern void uart_send(uchar dat);
extern void uart_received(uchar dat);

#endif