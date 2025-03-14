#ifndef __UI_MINER_SETTING_DATA_H
#define __UI_MINER_SETTING_DATA_H


#include "oled.h"
#include "stdbool.h"
void date_page(void);
void handle_date_page(RTC_DateTypeDef data,RTC_TimeTypeDef time,int i);
#endif

