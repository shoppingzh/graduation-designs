#include "reg51.h"
#include "sm.h"

void main(){

	sm_init();
	sm_x_speed(10);
	sm_y_speed(10);
	sm_x_start();

	while(1);
}
