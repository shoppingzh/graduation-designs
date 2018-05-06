#include "fpm10a.h"
#include "uart_syn.h"
#include "stdio.h"
#include "reg51.h"

code uchar packhead[] = {0xef, 0x01, 0xff, 0xff, 0xff, 0xff};
code uchar cmd_genimg[] = {0x01, 0x00, 0x03, 0x01, 0x00, 0x05};
code uchar cmd_img2char1[] = {0x01, 0x00, 0x04, 0x02, 0x01, 0x00, 0x08};
code uchar cmd_img2char2[] = (0x01, 0x00, 0x04, 0x02, 0x02, 0x00, 0x08);
code uchar cmd_regmodel[] = {0x01, 0x00, 0x03, 0x05, 0x00, 0x09};
code uchar cmd_template_num[] = {0x01, 0x00, 0x03, 0x1d, 0x00, 0x21};
code uchar cmd_clear_lib[] = {0x01, 0x00, 0x03, 0x0d, 0x00, 0x11};
code uchar cmd_open_light[] = {0x01, 0x00, 0x03, 0x50, 0x00, 0x54};
code uchar cmd_close_light[] = {0x01, 0x00, 0x03, 0x51, 0x00, 0x55};
code uchar cmd_echo[] = {0x01, 0x00, 0x03, 0x53, 0x00, 0x57};

/*************************************** STATIC FUNCTIONS ***************************************/

/**
* ��ʱN����
*/
static void delayms(uint t){
	uint i, j;
	for(i=0;i<t;i++)
		for(j=0;j<110;j++);	
}

/**
* У�鳤��Ϊ12��������Ϊ3��1�ֽ�ȷ�������ͨ�ذ�����
*/
static bit validate_common(uchar pack[]){
	uchar i;
	uint sum, temp;
	for(i=0;i<PACK_HEAD_LENGTH;i++){
		if(pack[i] != packhead[i]){
			return 0;
		}	
	}
	sum = pack[6] + pack[7] + pack[8] + pack[9];
	temp = pack[10];
	temp <<= 8;
	temp |= pack[11];
	if(sum != temp){
		return 0;
	}

	return 1;			
}

/**
* ���Ͱ�ͷ����
*/
static void send_packhead(){
	uchar i;
	for(i=0;i<6;i++){
		uart_send(packhead[i]);
	}
}

/**
* �������ݰ�
* @param pack	Ҫ���͵����ݰ�
* @param length �������ݰ��ĳ���
*/
static void send_pack(uchar pack[], uchar length){
	uchar i;
	for(i=0;i<length;i++){
		uart_send(pack[i]);
	}	
}

/**
* �������ݰ�
* @param pack 	Ҫ���յ����ݰ�
* @param length �������ݰ��ĳ���
*/
static void recv_pack(uchar pack[], uchar length){
	uchar i;
	ES = 0;
	for(i=0;i<length;i++){
		pack[i] = uart_receive();
	}
	ES = 1;
}

/**
* ����һ������ذ�
* @return ȷ���룬����0���ʾָ��ִ�гɹ�������ֵ��μ���������ȷ����
*/
static uchar recv_cmd_pack(){
	uchar recv[12];
	//���ջذ�
	recv_pack(recv, 12);
	//У��ذ�����������򷵻ش�����
	if(VALIDATOR && !validate_common(recv)){
		return RECEIVE_ERROR;
	}
	return recv[9];
}

/**
* ɾ��ָ�ƿ�������ģ�壨��index��ʼɾ��num��ģ�壩
* @param index	��ʼλ��
* @param num	ɾ���ĸ���
* @return ȷ���룺0x00ɾ���ɹ���0x01�հ�����0x10ɾ��ʧ��
*/
static uchar _fpm_delete_templates(uint index, uint num){
	uchar cmd[] = {0x01, 0x00, 0x07, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	uint sum;	
	//page
	cmd[4] = index >> 8;
	cmd[5] = index;
	//num
	cmd[6] = num >> 8;
	cmd[7] = num;
	//sum
	sum = 0x01 + 0x07 + 0x0c + index + num;
	cmd[8] = sum >> 8;
	cmd[9] = sum;

	send_packhead();
	send_pack(cmd, 10);
	
	return recv_cmd_pack();
}

/*************************************** API ***************************************/

/**
* ��ʼ��
*/
void fpm_init(){
	uart_init();
	delayms(500);
	//�ȴ����ֳɹ�
	//while(fpm_echo() != 0x55);
	//�رձ�����
	fpm_close_light();
}

/**
* ¼��ָ�Ƶ�ImageBufferͼ�λ�����
* @return ȷ���룺0¼��ɹ���1�հ�����2����������ָ�ƣ�3¼�벻�ɹ�
*/
uchar fpm_genimg(){
	send_packhead();
	send_pack(cmd_genimg, 6);
	return recv_cmd_pack();			
}

/**
* ��ImageBuffer�е�ͼ�����������ַ�
* @param which 	ָ���ַ���������1ѡ���ַ�������1��2ѡ���ַ�������2
* @return ȷ���룺0���ɳɹ���1�հ�����6ָ��ͼ��̫�ң�7������̫�٣�15ͼ�񻺳���û����Чͼ��
*/
uchar fpm_img2char(uchar which){
	switch(which){
		case 1:
			send_packhead();
			send_pack(cmd_img2char1, 7);
			break;
		case 2:
			send_packhead();
			send_pack(cmd_img2char2, 7);
			break;
		default:
			return RECEIVE_ERROR;
	}	
	return recv_cmd_pack();
}

/**
* ��CharBuffer1��CharBuffer2�е������ļ��ϲ���ָ��ģ�壬�������CharBuffer1��CharBuffer2������������ͬ��
* @return ȷ���룺0�ϲ��ɹ���1�հ�����0x0a�ϲ�ʧ�ܣ���öָ�Ʋ�ͬ��
*/
uchar fpm_regmodel(){
	send_packhead();
	send_pack(cmd_regmodel, 6);	
	return recv_cmd_pack();
}

/**
* ���һ��ָ�Ƶ�ָ�ƿ⣬�������̣��ɼ�ͼ�� + �������� + �����ϳ�ģ�� + �洢ģ��
* @param index	�洢λ��
* @return ȷ����
*/
uchar fpm_add_template(uint index){
	uchar cmd[] = {0x01, 0x00, 0x08, 0x54, 0x36, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00};
	uint sum;
	uchar first;
	//ָ�����
	cmd[6] = index >> 8;
	cmd[7] = index;
	sum =  0x01 + 0x08 + 0x54 + 0x36 + 0x02 + index;
	cmd[9] = sum >> 8;
	cmd[10] = sum;

	send_packhead();
	send_pack(cmd, 11);

	first = recv_cmd_pack();
	if(first == 0x56){
		return recv_cmd_pack();
	}
	return first;
}

/**
* ��ȡָ�ƿ�ģ������
* @return ģ������
*/
uint fpm_template_num(){
	uchar recv[14];
	uint num;
	send_packhead();
	send_pack(cmd_template_num, 6);
	recv_pack(recv, 14);
	if(recv[9] == 0x00){
		num = recv[10];
		num <<= 8;
		num |= recv[11];
		
		return num;	
	}	
	return 0;
}

/**
* ���ָ�ƿ�
* @return ȷ���룺0��ճɹ���1�հ�����0x11���ʧ��
*/
uchar fpm_clear_lib(){
	send_packhead();
	send_pack(cmd_clear_lib, 6);	
	return recv_cmd_pack();
}

/**
* ɾ��ָ�ƿ��е�һ��ָ��ģ��
* @param index	ָ��ģ�������λ��
* @return ȷ���룺0x00ɾ���ɹ���0x01�հ�����0x10ɾ��ʧ��
*/
uchar fpm_delete_template(uint index){
	return _fpm_delete_templates(index, 1);
}

/**
* �Զ��������������̣��ɼ�ָ�� + ͼ��ת���� + ����
* @param index	������ʼ����
* @param num	��������
* @return ��������ƥ��ɹ���ָ��������Ϊ-1��ʾû��������
*/
int fpm_auto_search(uint index, uint num){
	uchar cmd[16] = {0x01, 0x00, 0x08, 0x55, 0x36, /*index*/0x00, 0x00, /*num*/0x00, 0x00, /*sum*/0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	uint sum;
	cmd[5] = index >> 8;
	cmd[6] = index;
	cmd[7] = num >> 8;
	cmd[8] = num;
	sum = 0x01 + 0x08 + 0x55 + 0x36 + index + num;
	cmd[9] = sum >> 8;
	cmd[10] = sum;

	send_packhead();
	send_pack(cmd, 11);

	//��������
	recv_pack(cmd, 16);
	if(cmd[9] == 0x00){
		//sum���ã���Ϊƥ��÷�
		sum = 0;
		sum = cmd[12];
		sum <<= 8;
		sum |= cmd[13];
		//�÷ִ���0��ʾָ��ƥ�䣬�򷵻�������
		if(sum > 0){
			//sum���ã���Ϊָ������
			sum = 0;
			sum = cmd[10];	
			sum <<= 8;
			sum |= cmd[11];
			return sum;
		}
		return -1;
	}

	return -1;
}

/**
* ��ȡ������
* @param idxpage	����ҳ
* @return 32�ֽڵ���������Ϣ��ÿ���ֽڵ�ÿ��λ�����Ƿ���ָ��ģ�壬1Ϊ�У�0Ϊ��
* 	ע����ȡʧ�ܽ�����һ��32�ֽڵĿ�����
*/
uchar* fpm_read_index_table(uchar idxpage){
	//����-���ո��ð�
	idata uchar pack[44] = {/*send pack*/0x01, 0x00, 0x04, 0x1f, 0x00, 0x00, 0x00 /*receive pack ...*/};
	idata uchar table[32];
	idata uint sum;		
   	//��������ҳ
	pack[4] = idxpage;
	//sum
	sum = 0x01 + 0x04 + 0x1f + idxpage;
	pack[5] = sum >> 8;
	pack[6] = sum;
	
	send_packhead();
	send_pack(pack, 7);

	//���ջذ�
	recv_pack(pack, 44);
	//��������ɹ�
	if(pack[9] == 0x00){
		uchar i = 0, j;
		for(j=10;j<42;j++){
			table[i++] = pack[j];
		}
		return table;	
	}

	return table;
}

/**
* �򿪱�����
* @return ȷ���룺0x00�����ɹ���������ʧ��
*/
uchar fpm_open_light(){
	send_packhead();
	send_pack(cmd_open_light, 6);	
	return recv_cmd_pack();
}

/**
* �رձ�����
* @return ȷ���룺0x00�����ɹ���������ʧ��
*/
uchar fpm_close_light(){
	send_packhead();
	send_pack(cmd_close_light, 6);	
	return recv_cmd_pack();
}

/**
* ָ���豸����
* @return ȷ���룺0x55�豸�����������豸����
*/
uchar fpm_echo(){
	send_packhead();
	send_pack(cmd_echo, 6);
	return recv_cmd_pack();	
}
