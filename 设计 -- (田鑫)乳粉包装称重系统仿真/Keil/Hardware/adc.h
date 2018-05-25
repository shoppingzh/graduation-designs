#ifndef _ADC0808_H_
#define _ADC0808_H_

#ifndef uchar
	#define uchar unsigned char
#endif

extern void adc_init();
extern uchar adc_transform();

#endif