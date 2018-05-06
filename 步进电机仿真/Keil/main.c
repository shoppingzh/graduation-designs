#include <reg51.h>
#include "stepper_motor.h"

sbit key = P2^0;

void delay(){
	int i, j, k;
	for(i=0;i<200;i++)
		for(j=0;j<100;j++)
			for(k=0;k<20;k++);
}

void main(void) {

   	sm_config(1.8f);
	sm_init(SM_DIRECTION_FORWARD, 300);
	sm_start();
	
	while(1){
//		delay();
//		sm_speed(500);
//		delay();
//		sm_speed(700);
//		delay();
//		sm_speed(900);
	}	

}
