/*
	�����ģ���Ѿ���װ��ϣ��������Ը���
	���API��飺
		1. ��ʼ��
		2. ����X��Y����ת��
		3. ����X��Y����ת��
		4. ����X��Y����
		5. ֹͣX��Y����
		6. ����X��Y��������һ��ʱ��
		7. ����X��Y������ͬ����һ��ʱ��
*/
#include "reg51.h"
#include "sm.h"

#define uchar unsigned char

//��ʱ2s��ʵ������7s


/**
* MAIN
* ������ʵ��X��Y���ͬʱ���У�������Ϻ�ԭ·����
*/
void main(){

	sm_init();
	//sm_x_dir(SM_DIR_FORWARD);
	//sm_x_speed(600);
	//sm_x_start();

	//timer_init();
	//timer1_set_time(50000);
	//timer1_start();

	//sm_x_dir(SM_DIR_BACKWARD);
	//sm_x_speed(600);
	//sm_x_start();

	//sm_x_run(300, SM_DIR_FORWARD, 3000);
	//sm_x_run(300, SM_DIR_BACKWARD, 3000);

	while(1){

		sm_xy_run(500, SM_DIR_FORWARD, 300, SM_DIR_BACKWARD,2000);
		sm_xy_run(500, SM_DIR_BACKWARD, 300, SM_DIR_FORWARD, 2000);
		
		//sm_x_run(300, SM_DIR_FORWARD, 8000);
		//sm_x_run(300, SM_DIR_BACKWARD, 8000);	
	}
}
