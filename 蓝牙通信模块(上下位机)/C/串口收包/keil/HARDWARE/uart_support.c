#include "uart_support.h"

uchar pos = 0;
uchar packet[PACKET_SIZE];

static void save(uchar dat){
	packet[pos++] = dat;
}

void receive_byte(uchar rec_data){
	if(pos == 0 && rec_data == 0x55){
		save(rec_data);
	}else if(pos == 1 && rec_data == 0xaa){
		save(rec_data);
	}else if(pos == 2){
		save(rec_data);
	}else if(pos == 3){
		save(rec_data);
	}else if(pos == 4 && rec_data == 0xaa){
		save(rec_data);
	}else if(pos == 5 && rec_data == 0x55){
		uchar copy_packet[PACKET_SIZE];
		save(rec_data);
		memcpy(copy_packet, packet, PACKET_SIZE);
	   	receive_packet(copy_packet, PACKET_SIZE);
		pos = 0;
	}else{
		pos = 0;	
	}
	
}					 