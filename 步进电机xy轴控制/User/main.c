#include "sm.h"
#include "timer.h"

void main(){
	sm_init();
	sm_dir(SM_X, SM_DIR_FORWARD);
	sm_dir(SM_Y, SM_DIR_FORWARD);
	//sm_dir(SM_X, SM_DIR_BACKWARD);
	//sm_dir(SM_Y, SM_DIR_BACKWARD);
	sm_speed(SM_X, 40);
	sm_speed(SM_Y, 40);				
	sm_start(SM_X);
	sm_start(SM_Y);

	while(1);
}
