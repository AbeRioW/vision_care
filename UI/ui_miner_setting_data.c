#include "ui_miner_setting_data.h"
#include "stdio.h"
#include "ui_setting.h"

extern RTC_DateTypeDef get_data;  //获取日期结构体
extern RTC_TimeTypeDef get_time;  //获取时间结构体
extern RTC_HandleTypeDef hrtc;

static void show_date(RTC_DateTypeDef data,RTC_TimeTypeDef time,int i)
{
		char d_year[10]={0},d_mon[10]={0},d_day[10]={0},d_seek[10]={0},d_hour[10]={0},d_min[10]={0},d_sec[10]={0},week[20]={0};
		sprintf(d_year,"20%02d",data.Year);
		sprintf(d_mon,"%02d",data.Month);
		sprintf(d_day,"%02d",data.Date);
		
		sprintf(d_hour,"%02d",time.Hours);
		sprintf(d_min,"%02d",time.Minutes);
		sprintf(d_sec,"%02d",time.Seconds);
		
		OLED_ShowString(55,20,(uint8_t*)d_year,8,i==0?0:1);
		OLED_ShowString(80,20,(uint8_t*)"/",8,1);
		OLED_ShowString(90,20,(uint8_t*)d_mon,8,i==1?0:1);
		OLED_ShowString(100,20,(uint8_t*)"/",8,1);
		OLED_ShowString(110,20,(uint8_t*)d_day,8,i==2?0:1);
		
		
		OLED_ShowString(55,30,(uint8_t*)d_hour,8,i==3?0:1);
		OLED_ShowString(70,30,(uint8_t*)":",8,1);
		OLED_ShowString(80,30,(uint8_t*)d_min,8,i==4?0:1);
		OLED_ShowString(100,30,(uint8_t*)":",8,1);
		OLED_ShowString(110,30,(uint8_t*)d_sec,8,i==5?0:1);
			
		switch (data.WeekDay)
		{
				case RTC_WEEKDAY_MONDAY:
						sprintf(week,"%s","Mon");
				break;
				case RTC_WEEKDAY_TUESDAY:
						sprintf(week,"%s","Tues");
				break;
				case RTC_WEEKDAY_WEDNESDAY:
						sprintf(week,"%s","Wed");
				break;
				case RTC_WEEKDAY_THURSDAY:
						sprintf(week,"%s","Thur");
				break;
				case RTC_WEEKDAY_FRIDAY:
						sprintf(week,"%s","Fri");
				break;
				case RTC_WEEKDAY_SATURDAY:
						sprintf(week,"%s","Sat");
				break;
				case RTC_WEEKDAY_SUNDAY:
						sprintf(week,"%s","Sun");
						break;
				}
				OLED_ShowString(80,40,(uint8_t*)week,8,i==6?0:1);
				OLED_ShowString(80,50,(uint8_t*)"back",8,i==7?0:1);
				OLED_Refresh(); 
}

//日期的home界面
void date_page(void)
{
	show_date(get_data,get_time,8);   //默认都不选中
}

void handle_date_page(RTC_DateTypeDef data,RTC_TimeTypeDef time,int i)
{
	  int position = 0;
	  bool enter_view = false;
	  while(1)
		{
			if(button==LEFT_BUTTON)
			{
				 button = UNPRESSED;
         position--;
         if(position<0)
				 {
						position=7;
				 }					 
			}
			
			if(button==RIGHT_BUTTON)
			{
				button = UNPRESSED;
				position++;
				if(position>7)
				{
						position=0;
				}
			}
			
			if(button==ENSURE_BUTTON)
			{
					button = UNPRESSED;
				  enter_view = true;
			}
			
			show_date(data,time,position);
			if(enter_view)
			{
				  enter_view = false;
					switch(position)
					{
						case 0:
								data.Year++;
								if(data.Year>99)
									data.Year=20;
						break;
						case 1:
								data.Month++;
								if(data.Month>12)
									data.Month=1;
						break;
						case 2:
								data.Date++;
								if(data.Date>31)
									data.Date=1;
						break;
						case 3:
								time.Hours++;
								if(time.Hours>23)
									time.Hours=0;
						break;
						case 4:
								time.Minutes++;
								if(time.Minutes>59)
									time.Minutes=0;
						break;
						case 5:
								time.Seconds++;
								if(time.Seconds>59)
									time.Seconds=0;
						break;
						case 6:
								data.WeekDay++;
								if(data.WeekDay>7)
									data.WeekDay=1;
						break;
						case 7:
								//保存被退出
						    HAL_RTC_SetTime(&hrtc,&time,RTC_FORMAT_BIN);
						    HAL_RTC_SetDate(&hrtc,&data,RTC_FORMAT_BIN);
						    return;
						break;
					}
			}
			
		}
}
