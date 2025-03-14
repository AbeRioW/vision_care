#include "ui_home.h"
#include "rtc.h"
#include "sr04.h"
#include "adc.h"
#include "ecb02.h"
#include "ui_setting.h"

float light_dim  = 0.2;    //�ɵ���
float loght_bright = 2.6;  //
bool home_page = true;

extern bool distance_boundary;

static bool ble_connected = false;

static uint8_t  uart_too_close[19]={0xFD,0x00,0x10,0x01,0x01,0xBE,0xE0,0xC0,0xEB,0xCC,0xAB,0xBD,0xFC,0xC7,0xEB,0xD7,0xF8,0xD6,0xB1};  //����̫������ֱ
static uint8_t  uart_too_dark[13]={0xFD,0x00,0x0A,0x01,0x01,0xB9,0xE2,0xCF,0xDF,0xCC,0xAB,0xB0,0xB5};    //����̫��
static uint8_t  uart_too_light[13]= {0xFD,0x00,0x0A,0x01,0x01,0xB9,0xE2,0xCF,0xDF,0xCC,0xAB,0xC7,0xBF};    //����̫��

//����ͼ��
const uint8_t bmp_ble[32]={0x00,0x00,0x00,0x00,0x00,0x10,0x20,0x40,
									       0xFE,0x44,0x28,0x10,0x00,0x00,0x00,0x00,
												 0x00,0x00,0x00,0x00,0x00,0x04,0x02,0x01,
												 0x3F,0x11,0x0A,0x04,0x00,0x00,0x00,0x00};

void ui_home(void)
{
	  char date[100]={0};
		char time[100]={0}; 
		char week[100]={0};
		float adcy;
		uint16_t adcx = 0;
		
		if(button==ENSURE_BUTTON)
		{
			  OLED_Clear();
			  home_page = false;
			  button=UNPRESSED;
				ui_setting();
		}

		
		if(home_page)
		{
		sr04_getdata();
		//�������
		if(distance_boundary)  //������
		{
				distance_boundary = false;
			
			  //ͨ�������������ݳ�ȥ
			  if(ble_connected&&rtc_update)    //����ط�����һ��������һ���ӷ���һ��
				{
						HAL_UART_Transmit(&huart1,(uint8_t*)"too close",9,0xffff);
				}
		}
		
		
		//�������յ�������
		if(rx1_end_flag == true)  
		{
				rx1_end_flag=false;
			  if(ecb02_connected())
				{
					  ble_connected = true;
					  OLED_ShowPicture(0,0,16,16,(uint8_t*)bmp_ble,0);
             					
				}
				else if(ecb02_disconnected())
				{
            ble_connected = false;	
            for(int i=0;i<16;i++)
					  {
								for(int j=0;j<16;j++)
							  OLED_DrawPoint(i,j,0);
						}
				}
				memset(uart1_rx,0,100);
				rx1_count=0;
			  HAL_UART_Receive_DMA(&huart1,uart1_rx,100);   //��Ҫ���´�DMA����
		}

		
		if(rtc_update)    //ʱ����ʾ
		{
				rtc_update = false;

			  sprintf(date,"20%02d/%02d/%02d",get_data.Year,get_data.Month,get_data.Date);
			  sprintf(time,"%02d:%02d:%02d",get_time.Hours,get_time.Minutes,get_time.Seconds);
				switch (get_data.WeekDay)
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
			
			  OLED_ShowString(20,20,(uint8_t*)date,16,1);
	      OLED_ShowString(30,40,(uint8_t*)time,16,1);
				OLED_ShowString(90,0,(uint8_t*)week,16,1);
			  OLED_Refresh();  
				
				//����ADC������
				HAL_ADC_Start(&hadc1);   
				HAL_ADC_PollForConversion(&hadc1,10); //�ȴ�ADCת�����
				adcx = (uint16_t)HAL_ADC_GetValue(&hadc1);   //����adת�����������
				adcy = (float)adcx*3.3/4096;             //ת��Ϊʵ�ʵ�ѹ
				if(adcy<light_dim)   //̫����
				{
						//HAL_UART_Transmit(&huart2,uart_too_light,13,0xffff);
            HAL_UART_Transmit(&huart1,(uint8_t*)"too light",9,0xffff);					
				}
				else if(adcy>loght_bright)  //̫����
				{					
					  //HAL_UART_Transmit(&huart2,uart_too_dark,13,0xffff);	
					  HAL_UART_Transmit(&huart1,(uint8_t*)"too dark",8,0xffff);	
				}

		}
		
	}


}