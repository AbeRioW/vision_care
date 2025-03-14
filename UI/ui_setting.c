#include "ui_setting.h"
#include "ui_miner_setting_data.h"
#include "ui_miner_setting_lighting.h"
#include "ui_miner_setting_distance.h"

#include "stdio.h"

int pageview = 0;

extern RTC_DateTypeDef get_data;  //获取日期结构体
extern RTC_TimeTypeDef get_time;  //获取时间结构体

extern float light_dim;    //可调节
extern float loght_bright;  //
extern uint8_t distance_legth;
extern bool home_page;
void ui_setting(void)
{
	char date_show[100]={0x00};
	bool enter_view = 0;
	OLED_ShowString(40,0,(uint8_t*)"Setting",16,1);
	OLED_DrawLine(0,17,127,17,1);
	
	OLED_ShowString(0,20,(uint8_t*)"Data",8,0);
	OLED_ShowString(0,30,(uint8_t*)"Light",8,1);
	OLED_ShowString(0,40,(uint8_t*)"Distance",8,1);
	OLED_ShowString(0,50,(uint8_t*)"Back",8,1);
	OLED_DrawLine(50,20,50,63,1);
	
		
	while(1)
	{
			if(button==LEFT_BUTTON)
			{
				 button = UNPRESSED;
         pageview--;
         if(pageview<0)
				 {
						pageview=3;
				 }					 
			}
			
			if(button==RIGHT_BUTTON)
			{
				button = UNPRESSED;
				pageview++;
				if(pageview>3)
				{
						pageview=0;
				}
			}
			
			if(button==ENSURE_BUTTON)
			{
					button = UNPRESSED;
				  enter_view = true;
			}
			
			//页面的切换
			HAL_Delay(300);             //界面按键反应的快慢可以调节这个参数值
			switch(pageview)
			{
				case 0:
					OLED_ShowString(0,20,(uint8_t*)"Data",8,0);
					OLED_ShowString(0,30,(uint8_t*)"Light",8,1);
					OLED_ShowString(0,40,(uint8_t*)"Distance",8,1);
					OLED_ShowString(0,50,(uint8_t*)"Back",8,1);
				  clear_view();
					date_page();
					break;
				case 1:
					OLED_ShowString(0,20,(uint8_t*)"Data",8,1);
					OLED_ShowString(0,30,(uint8_t*)"Light",8,0);
					OLED_ShowString(0,40,(uint8_t*)"Distance",8,1);
					OLED_ShowString(0,50,(uint8_t*)"Back",8,1);
				  clear_view();
					light_page();
					break;
				case 2:
					OLED_ShowString(0,20,(uint8_t*)"Data",8,1);
					OLED_ShowString(0,30,(uint8_t*)"Light",8,1);
					OLED_ShowString(0,40,(uint8_t*)"Distance",8,0);
					OLED_ShowString(0,50,(uint8_t*)"Back",8,1);
				  clear_view();
					distance_page();
					break;
				case 3:
					OLED_ShowString(0,20,(uint8_t*)"Data",8,1);
					OLED_ShowString(0,30,(uint8_t*)"Light",8,1);
					OLED_ShowString(0,40,(uint8_t*)"Distance",8,1);
					OLED_ShowString(0,50,(uint8_t*)"Back",8,0);
				  clear_view();
				  OLED_Refresh();
					break;
				default:
					break;
			}
			
			if(enter_view)
			{
					enter_view=false;
				  switch(pageview)
					{
						case 0:
							handle_date_page(get_data,get_time,0);
						break;
						case 1:
							handle_light_page(light_dim,loght_bright,0);
						break;
						case 2:
							handle_distance_page(0);
							break;
						case 3:
							home_page = true;
						  button = UNPRESSED;
						  OLED_Clear();
							return;
						default:
							break;
					}
			}
	}
						
}




void clear_view(void)
{
			for(int i=51;i<128;i++)
			{
						for(int j=20;j<64;j++)
						{
								OLED_DrawPoint(i,j,0);
						}
			}
}
