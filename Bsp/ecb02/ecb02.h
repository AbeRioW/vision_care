#ifndef __ECB02_H
#define __ECB02_H

#include "stdbool.h"
#include "stdint.h"
#include "string.h"
#include "main.h"
#include "usart.h"

#define AT_REC_OK   		"OK\r\n"
#define AT          		"AT\r\n"
#define AT_VERSION  		"AT+VER?\r\n"

#define AT_CONNECT  		"CONNECT OK\r\n"
#define AT_DISCONNECT		"DISCONNECT\r\n"


void query_ecb02(void);
bool ecb02_exist(void);
bool ecb02_connected(void);
bool ecb02_disconnected(void);

#endif

