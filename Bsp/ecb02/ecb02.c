#include "ecb02.h"

extern uint8_t uart1_rx[100];
extern uint8_t rx1_count;
extern bool rx1_end_flag;


//返回的数据  +VER:12.2.13\r\nOK\r\n
bool ecb02_exist(void)
{
	 bool ret =false;
	(strstr((const char*)AT_REC_OK,(const char*)uart1_rx)!=NULL)?(ret=true):(ret=false);
	return ret;
}

bool ecb02_connected(void)
{
	bool ret =false;
	(strstr((const char*)AT_CONNECT,(const char*)uart1_rx)!=NULL)?(ret=true):(ret=false);
	return ret;
}


bool ecb02_disconnected(void)
{
	bool ret =false;
	(strstr((const char*)AT_DISCONNECT,(const char*)uart1_rx)!=NULL)?(ret=true):(ret=false);
	return ret;
}


//发送查询的AT指令
void query_ecb02(void)
{
		HAL_UART_Transmit(&huart1,(uint8_t*)(AT_VERSION),9,0xffff);
}

