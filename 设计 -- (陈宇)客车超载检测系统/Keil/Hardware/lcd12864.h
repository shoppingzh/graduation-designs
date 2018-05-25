#ifndef _LCD12864_H_
#define _LCD12864_H_

#define uchar unsigned char
#define uint unsigned int

extern void 	lcd_init();
extern void 	lcd_write_com(uchar com);
extern void 	lcd_write_data(uchar dat);
extern uchar 	lcd_read_data();
extern void 	lcd_draw_point(uchar x, uchar y);
extern void 	lcd_graphics_clear();
extern void		lcd_display_ascii(uchar row, uchar col, char left, char right);
extern void 	lcd_display_string(uchar row, uchar col, char* str);
extern void		lcd_display_digit(uchar row, uchar col, uint d);
extern void		lcd_clear();
extern void 	lcd_clear_line(uchar line);

#endif