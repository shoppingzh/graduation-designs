#include "binary.h"

/**
* ��ȡһ���ֽڸ�λ��λ��
* @param val	�ֽ�
* @return ��λλ����������0101 1011�򷵻�{0, 1, 3, 4, 6, -1, -1, -1}
*/
char* get_high_bits(uchar val){
	char rst[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
	uchar i = 0, index = 0;
	while(val){
		if(val & 1){
			rst[i++] = index;			
		}
		index++;
		val >>= 1;
	}
	return rst; 
}
