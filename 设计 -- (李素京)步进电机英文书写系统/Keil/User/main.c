#include "reg51.h"
#include "writer.h"
#include "uart.h"

code uchar A[] = {50, 10, 1, 30, 90, 2, 50, 10, 1, 70, 90, 2, 40, 50, 1, 60, 50, 2};
code uchar *arr[52] = {A};
code uchar lens[] = {18};

bit writing = 0;		//�Ƿ���д��־λ
uchar curr = 0;

void main(){

	IP = 0x10;
	writer_init();		
 
	while(1){

		if(writing){
			writer_write(arr[curr], lens[curr]);
			writing = 0;
		}		

	}
}

/**
* ���յ���λ��ͨ������������������
* @param cmd 	�ص�������Ϊ����������������
*/
void uart_received(uchar cmd){
	if(cmd >= 'A' && cmd <= 'Z'){
		curr = cmd - 'A';
		writing = 1;			
	}else if(cmd >= 'a' && cmd <= 'z'){
		curr = cmd - 'a';
		writing = 1;
	}
}


