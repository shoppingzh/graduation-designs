#include "key.h"
#include "pyinput.h"
#include "string.h"
#include "lcd12864.h"
#include "intrins.h"
#include "stdio.h"

#ifndef uchar
	#define uchar unsigned char
#endif

char input_buffer[8];					//���뻺�������磺"524"
int input_index = 0;					//��ǰ���뻺������λ��

py_index *matchs[10];					//��ǰ�����ƴ����ƥ������к�����Ϣ
char *opt_words;						//��ǰ���б�ѡ���֣���"wang"��Ӧ"��������������"
uchar opt_idx = 0;						//��ǰ��ѡ��������
char page_words[9]; 					//��ǰҳ�ı�ѡ���֣�1��ֻ��ʾ4�����֣���"wang"��Ӧ"1.��2.��3.��4.��"
uchar page = 0;							//ҳ����ƴ��ƥ��ĺ���ÿ4������Ϊ1ҳ��Ĭ����ʾ��һҳ
char words_buffer[65];					//��Ļ���ֻ�����
uchar words_idx = 0;					//���ֻ�����������ָʾ��ǰ��Ļ���ֵĸ���

uchar row = 0; 							//��ǰ��ʾ����
uchar col = 1;						   	//��ǰ��ʾ����

bit writing = 0;						//�Ƿ�����д״̬
bit flag = 1;							//���״̬λ
uchar count = 0;						//��ʱ������

//��ͨ��ʱ
static void delay(uchar t){
	uchar i,j;
	for(i=0;i<t;i++)
		for(j=0;j<110;j++);
}


//���������
static void clear_input_buffer(){
	uchar i;
	for(i=0;i<8;i++){
		input_buffer[i] = 0;
	}
}

//��ʾ��ǰ�����ƴ���ַ�
static void show_letters(){
	uchar line[17], i, *py;
	//���ƴ����ʾ��
	clearline(2);

	for(i=0;i<17;i++){
		line[i] = '\0';	
	}
	py = matchs[0][0].py;
	for(i=0;i<16;i++){
		if(! *py)
			continue;

		line[i] = *py;
		py++;		
	}
	displaystring(2, 0, line);
}

//��ʾ��ѡ��
static void show_options(){
	uchar start = page*8, i, page_content[17], idx = 0;
	opt_words = matchs[0][0].pymb;

	//��յ�ǰҳ����
	clearline(3);

	//����ǰ���ҳ��
	for(i=0;i<start;i++){
		if(! *opt_words)
			break;
		opt_words++;
	}
	//��ȡ��ǰҳ����
	strncpy(page_words, opt_words, 8);
	page_words[8] = '\0';
	//���ɵ�ǰҳ���ݣ��磺"1.��2.��3.��4.��"
	for(i=0;i<16;i++){
		uchar c = i / 2;
		//���
		if(c % 2 == 0){
			//����
			if(i % 2 == 0){
				uchar order = (i / 4) + 1;
				//�����ǰ���ڱ�ѡ������ʾ��Ŷ�����ʾ"*"
				if(order == opt_idx + 1){
					page_content[i] =  '*';
				}else{
					page_content[i] = order + 48;
				}	
			}else{
				//��
				page_content[i] = '.';
			}		
		}else{
			//����
			page_content[i] = page_words[idx++];
		}	
	}
	page_content[16] = '\0';	

	//��ʾ��ǰҳ������
	displaystring(3, 0, page_content);
}

//��һҳ
static void prev_page(){
	if(page > 0){
		page--;
		opt_idx = 3;
	}		
}

//��һҳ
static void next_page(){
	page++;
	opt_idx = 0;
}

//����Ļ��дһ������
static void write_word(uchar *word){
	//д����ĩ
	if(col > 7){
		row++;
		col = 0;
		//�ı���д������������
		if(row > 1){
			clearline(0);
			clearline(1);
			row = 0;
			col = 1;
		}
	}
	
	//��ʾ��ǰ����
	displaystring(row, col++, word);

	//����ǰ���ִ洢��������
//	if(words_idx < 61){
//		words_buffer[words_idx++] = word[0];
//		words_buffer[words_idx++] = word[1];	
//	}	
}

//����Ļ����ʾ��ǰ����
static void show_current(){
	uchar word[3] = {0, 0, 0}, idx;

	//��ȡ��ǰ����
	idx = opt_idx * 2;
	word[0] = page_words[idx];
	word[1] = page_words[idx + 1];

	write_word(word);	
}

//ɾ��һ������
static void delete_word(){
	if(row >= 0){
		if(col > 0){
			col--;
		}else{
			if(row > 0){
				col = 7;
				row--;
			}
		}
	}
	displaystring(row, col, "  ");
}


//��ʱ����ʼ��
static void timer_init(){
	TMOD = 0x01;
	TH0 = 0x3c;
	TL0 = 0xb0;
	EA = 1;
	ET0 = 1;
	//TR0 = 1;
}	   	

void main(){
	initlcm();
	displaystring(2, 0, "��ӭʹ�����뷨��");
	displaystring(3, 0, "�����������Կ���");

	timer_init();

	while(1){
		int key = keyscan();

		if(key == -1){
			//����
		}else if(key == 0){	
			//������д״̬���ո�������Ļ����дһ���ո�
			if(!writing){
				write_word("  ");
				continue;	
			}
			//����0��������ǰ������ʾ����Ļ��
			show_current();			

			//����
			clear_input_buffer();
			input_index = 0;
			opt_idx = 0;
			writing = 0;

			clearline(2);				
			clearline(3);			
		}else if(key == 1){
		 	//����1����������رչ��
			if(TR0)
				TR0 = 0;
			else{
				TR0 = 1;
				displaystring(2, 2, "�����͹��ܣ�");
				displaystring(3, 0, "�����ʹ�ã�");
			} 
				
		}else if(key == 10){
			if(!writing){
				//�����ǰ��������д״̬������*��ɾ��һ����Ļ�ϵ����к���
				delete_word();
				continue;
			}

			//��ѡ�����б�����һλ
			if(opt_idx > 0){
				opt_idx--;
			}else{
				prev_page();
			}
			show_options();		
		}else if(key == 11){
			if(!writing){
				//ȫ����ʾ����ʾ���ֻ���������������
				//full_screen();
				continue;	
			}
				
			//��ѡ�����б�����һλ
			if(opt_idx < 3){
				opt_idx++;
			}else{
				next_page();
			}
			show_options();
		}else{
			if(input_index > 5){
				continue;
			}
			writing = 1;
			page = 0;

			//�������룬��ȡ�����ƴ���ͺ���
			input_buffer[input_index++] = key + 48;
			get_matched_pymb(input_buffer, matchs);

			//��ʾ�����ƴ���ַ�
			show_letters();
			
			//��ʾ��ѡ��
			show_options();
		}
	}
}

//��ʱ��0�жϣ�������ʾ���
void timer0_int() interrupt 1{
	uchar r, c;
	TH0 = 0x3c;
	TL0 = 0xb0;
	if(count++ < 10)
		return;

	count = 0;

	//����һ�ݣ���ֹrow��col����̬����
	r = row;
	c = col;

	if(flag){
		displaystring(r, c, "_");	
	}else{
		displaystring(r, c, "  ");
	}
	flag = ~flag;
	
}
