#include "ui_miner_setting_distance.h"

extern uint8_t distance_legth;
static void distance_view(int i)
{
	char vew_d[10]={0x00};
	OLED_ShowString(65,30,(uint8_t*)"-",8,i==0?0:1);
	//OLED_ShowString(75,30,(uint8_t*)"50",8,1);
	sprintf(vew_d,"%02d",distance_legth);
	OLED_ShowString(75,30,(uint8_t*)vew_d,8,1);
	OLED_ShowString(90,30,(uint8_t*)"+",8,i==1?0:1);
	OLED_ShowString(103,30,(uint8_t*)"(cm)",8,1);
	OLED_ShowString(70,40,(uint8_t*)"back",16,i==2?0:1);
	OLED_Refresh();
}

void distance_page(void)
{
		distance_view(3);
}


void handle_distance_page(int i)
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
						position=2;
				 }					 
			}
			
			if(button==RIGHT_BUTTON)
			{
				button = UNPRESSED;
				position++;
				if(position>2)
				{
						position=0;
				}
			}
			
			if(button==ENSURE_BUTTON)
			{
					button = UNPRESSED;
				  enter_view = true;
			}
			HAL_Delay(200);        //按键太灵敏或者不灵敏可以调这个参数
			distance_view(position);
			
			if(enter_view)
			{
					enter_view = false;
				  switch(position)
					{
						case 0:
							   distance_legth--;
						     if(distance_legth<0)
										distance_legth=0;
							break;
						case 1:
								distance_legth++;
								 if(distance_legth>50)
									 distance_legth = 50;
							break;
						case 2:
								return;
							break;
					}
			}
		}
}


