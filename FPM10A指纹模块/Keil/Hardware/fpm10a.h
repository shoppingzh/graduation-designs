#ifndef _FPM10A_H_
#define _FPM10A_H_

#ifndef uchar
	#define uchar unsigned char
#endif
#ifndef uint
	#define uint unsigned int
#endif

#define PACK_HEAD_LENGTH 6
#define VALIDATOR 1
#define RECEIVE_ERROR 0x01

extern void 	fpm_init();
extern uchar 	fpm_genimg();
extern uchar 	fpm_img2char(uchar which);
extern uchar 	fpm_regmodel();
extern uchar 	fpm_add_template(uint index);
extern uint 	fpm_template_num();
extern uchar 	fpm_clear_lib();
extern uchar	fpm_delete_template(uint index);
extern uint		fpm_auto_search(uint index, uint num);

extern uchar	fpm_open_light();
extern uchar	fpm_close_light();
extern uchar	fpm_echo();


#endif