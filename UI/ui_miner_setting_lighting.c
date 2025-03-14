#include "ui_miner_setting_lighting.h"
#include "math.h"
#include "float.h"

extern float light_dim;    //¿Éµ÷½Ú
extern float loght_bright;  //

static void show_lighting(float dim,float bright,int i)
{
  char d_dim[20]={0};
	char d_bright[20]={0};
	
	OLED_ShowString(55,20,(uint8_t*)"-",8,i==0?0:1);
	sprintf(d_dim,"%0.2f",dim);
	OLED_ShowString(65,20,(uint8_t*)d_dim,8,1);
	OLED_ShowString(90,20,(uint8_t*)"+",8,i==1?0:1);
	OLED_ShowString(100,20,(uint8_t*)"min",8,1);
	
	OLED_ShowString(55,30,(uint8_t*)"-",8,i==2?0:1);
	sprintf(d_bright,"%0.2f",bright);
	OLED_ShowString(65,30,(uint8_t*)d_bright,8,1);
	OLED_ShowString(90,30,(uint8_t*)"+",8,i==3?0:1);
	OLED_ShowString(100,30,(uint8_t*)"max",8,1);
	
	OLED_ShowString(70,40,(uint8_t*)"back",8,i==4?0:1);
	OLED_ShowString(55,48,(uint8_t*)"(smaller is",8,1);
	OLED_ShowString(55,56,(uint8_t*)"brghter)",8,1);
	OLED_Refresh();
	
}


void light_page(void)
{
		show_lighting(light_dim,loght_bright,5);
}


void handle_light_page(float dim,float bright,int i)
{
	  float num = 0.0f;
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
						position=4;
				 }					 
			}
			
			if(button==RIGHT_BUTTON)
			{
				button = UNPRESSED;
				position++;
				if(position>4)
				{
						position=0;
				}
			}
			
			if(button==ENSURE_BUTTON)
			{
					button = UNPRESSED;
				  enter_view = true;
			}
			
			show_lighting(dim,bright,position);
			
			if(enter_view)
			{
				  enter_view = false;
					switch(position)
					{
						case 0:
									dim=dim-0.1;
									if(dim<FLT_EPSILON)
									{
											dim=0;
									}
									
						break;
						case 1:
									dim=dim+0.1;
									if(dim-1.0f>FLT_EPSILON)
										dim=1;
						break;
						case 2:
									bright=bright-0.1;
										if(bright<FLT_EPSILON)
											bright=0;
						break;
						case 3:
									bright=bright+0.1;
									if(bright-4.0f>FLT_EPSILON)
										bright=4;
						break;
						case 4:
									return;
						break;
					}
			}
			
		}
}
