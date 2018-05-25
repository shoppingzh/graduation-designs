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
* 延时N毫秒
*/
static void delayms(uint t){
	uint i, j;
	for(i=0;i<t;i++)
		for(j=0;j<110;j++);	
}

/**
* 校验长度为12、包长度为3、1字节确认码的普通回包数据
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
* 发送包头数据
*/
static void send_packhead(){
	uchar i;
	for(i=0;i<6;i++){
		uart_send(packhead[i]);
	}
}

/**
* 发送数据包
* @param pack	要发送的数据包
* @param length 发送数据包的长度
*/
static void send_pack(uchar pack[], uchar length){
	uchar i;
	for(i=0;i<length;i++){
		uart_send(pack[i]);
	}	
}

/**
* 接收数据包
* @param pack 	要接收的数据包
* @param length 接收数据包的长度
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
* 接收一个命令回包
* @return 确认码，返回0则表示指令执行成功，其它值请参见具体命令确认码
*/
static uchar recv_cmd_pack(){
	uchar recv[12];
	//接收回包
	recv_pack(recv, 12);
	//校验回包，如果错误则返回错误码
	if(VALIDATOR && !validate_common(recv)){
		return RECEIVE_ERROR;
	}
	return recv[9];
}

/**
* 删除指纹库中任意模板（从index开始删除num个模板）
* @param index	开始位置
* @param num	删除的个数
* @return 确认码：0x00删除成功，0x01收包有误，0x10删除失败
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
* 初始化
*/
void fpm_init(){
	uart_init();
	delayms(500);
	//等待握手成功
	//while(fpm_echo() != 0x55);
	//关闭背景灯
	fpm_close_light();
}

/**
* 录入指纹到ImageBuffer图形缓冲区
* @return 确认码：0录入成功，1收包有误，2传感器上无指纹，3录入不成功
*/
uchar fpm_genimg(){
	send_packhead();
	send_pack(cmd_genimg, 6);
	return recv_cmd_pack();			
}

/**
* 将ImageBuffer中的图像生成特征字符
* @param which 	指定字符缓冲区，1选择字符缓冲区1，2选择字符缓冲区2
* @return 确认码：0生成成功，1收包有误，6指纹图像太乱，7特征点太少，15图像缓冲区没有有效图像
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
* 将CharBuffer1与CharBuffer2中的特征文件合并成指纹模板，结果存于CharBuffer1与CharBuffer2（两者内容相同）
* @return 确认码：0合并成功，1收包有误，0x0a合并失败（两枚指纹不同）
*/
uchar fpm_regmodel(){
	send_packhead();
	send_pack(cmd_regmodel, 6);	
	return recv_cmd_pack();
}

/**
* 添加一个指纹到指纹库，包含过程：采集图像 + 生成特征 + 特征合成模板 + 存储模板
* @param index	存储位置
* @return 确认码
*/
uchar fpm_add_template(uint index){
	uchar cmd[] = {0x01, 0x00, 0x08, 0x54, 0x36, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00};
	uint sum;
	uchar first;
	//指定序号
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
* 获取指纹库模板数量
* @return 模板数量
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
* 清空指纹库
* @return 确认码：0清空成功，1收包有误，0x11清空失败
*/
uchar fpm_clear_lib(){
	send_packhead();
	send_pack(cmd_clear_lib, 6);	
	return recv_cmd_pack();
}

/**
* 删除指纹库中的一个指纹模板
* @param index	指定模板的索引位置
* @return 确认码：0x00删除成功，0x01收包有误，0x10删除失败
*/
uchar fpm_delete_template(uint index){
	return _fpm_delete_templates(index, 1);
}

/**
* 自动搜索，包含过程：采集指纹 + 图像转特征 + 搜索
* @param index	搜索开始索引
* @param num	搜索数量
* @return 搜索到的匹配成功的指纹索引，为-1表示没有搜索到
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

	//复用数组
	recv_pack(cmd, 16);
	if(cmd[9] == 0x00){
		//sum复用，作为匹配得分
		sum = 0;
		sum = cmd[12];
		sum <<= 8;
		sum |= cmd[13];
		//得分大于0表示指纹匹配，则返回其索引
		if(sum > 0){
			//sum复用，作为指纹索引
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
* 读取索引表
* @param idxpage	索引页
* @return 32字节的索引表信息，每个字节的每个位代表是否有指纹模板，1为有，0为无
* 	注：读取失败将返回一个32字节的空数组
*/
uchar* fpm_read_index_table(uchar idxpage){
	//发送-接收复用包
	idata uchar pack[44] = {/*send pack*/0x01, 0x00, 0x04, 0x1f, 0x00, 0x00, 0x00 /*receive pack ...*/};
	idata uchar table[32];
	idata uint sum;		
   	//设置索引页
	pack[4] = idxpage;
	//sum
	sum = 0x01 + 0x04 + 0x1f + idxpage;
	pack[5] = sum >> 8;
	pack[6] = sum;
	
	send_packhead();
	send_pack(pack, 7);

	//接收回包
	recv_pack(pack, 44);
	//读索引表成功
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
* 打开背景灯
* @return 确认码：0x00操作成功，其它表失败
*/
uchar fpm_open_light(){
	send_packhead();
	send_pack(cmd_open_light, 6);	
	return recv_cmd_pack();
}

/**
* 关闭背景灯
* @return 确认码：0x00操作成功，其它表失败
*/
uchar fpm_close_light(){
	send_packhead();
	send_pack(cmd_close_light, 6);	
	return recv_cmd_pack();
}

/**
* 指纹设备握手
* @return 确认码：0x55设备正常，否则设备故障
*/
uchar fpm_echo(){
	send_packhead();
	send_pack(cmd_echo, 6);
	return recv_cmd_pack();	
}
