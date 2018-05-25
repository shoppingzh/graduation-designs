#include "binary.h"

/**
* 获取一个字节高位的位置
* @param val	字节
* @return 高位位置索引，如0101 1011则返回{0, 1, 3, 4, 6, -1, -1, -1}
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
