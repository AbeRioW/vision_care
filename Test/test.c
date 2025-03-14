#include "test.h"

//���������test
#include "stdio.h"
#include "stdbool.h"
#include "string.h"
#include "stdint.h"
#include "ecb02.h"
#include "oled.h"

extern uint8_t uart1_rx[100];
extern uint8_t rx1_count;
extern bool rx1_end_flag;

void uart1_test(void)
{
	  int i=0;
		if(rx1_end_flag)
		{
				rx1_end_flag=false;
			  printf("���յ�����:");
			  for(i=0;i<rx1_count;i++)
			  {
						printf("%02x",uart1_rx[i]);
				}
				printf("\r\n");
			
			  rx1_count=0;
			  memset(uart1_rx,0,100);
			  HAL_UART_Receive_DMA(&huart1,uart1_rx,100);  //��Ҫ��������DMA
		}
}


void ecb02_test(void)
{
		if(rx1_end_flag)
		{
				rx1_end_flag=false;
			
			  if(ecb02_connected())
				{
						printf("������\r\n");
				}
				
				if(ecb02_disconnected())
				{
						printf("�ѶϿ�\r\n");
				}
			
			  rx1_count=0;
			  memset(uart1_rx,0,100);
			  HAL_UART_Receive_DMA(&huart1,uart1_rx,100);  //��Ҫ��������DMA
		}
}

void oled_test(void)
{
	  uint8_t t=' ';
		OLED_ShowChinese(0,0,0,16,1);//��
		OLED_ShowChinese(18,0,1,16,1);//��
		OLED_ShowChinese(36,0,2,16,1);//԰
		OLED_ShowChinese(54,0,3,16,1);//��
		OLED_ShowChinese(72,0,4,16,1);//��
		OLED_ShowChinese(90,0,5,16,1);//��
		OLED_ShowChinese(108,0,6,16,1);//��
		OLED_ShowString(8,16,"ZHONGJINGYUAN",16,1);
		OLED_ShowString(20,32,"2014/05/01",16,1);
		OLED_ShowString(0,48,"ASCII:",16,1);  
		OLED_ShowString(63,48,"CODE:",16,1);
		OLED_ShowChar(48,48,t,16,1);//��ʾASCII�ַ�	   
		t++;
		if(t>'~')t=' ';
		OLED_ShowNum(103,48,t,3,16,1);
		OLED_Refresh();
		HAL_Delay(500);
		OLED_Clear();
		OLED_ShowChinese(0,0,0,16,1);  //16*16 ��
	  OLED_ShowChinese(16,0,0,24,1); //24*24 ��
		OLED_ShowChinese(24,20,0,32,1);//32*32 ��
	  OLED_ShowChinese(64,0,0,64,1); //64*64 ��
		OLED_Refresh();
	  HAL_Delay(500);
  	OLED_Clear();
		OLED_ShowString(0,0,"ABC",8,1);//6*8 ��ABC��
		OLED_ShowString(0,8,"ABC",12,1);//6*12 ��ABC��
	  OLED_ShowString(0,20,"ABC",16,1);//8*16 ��ABC��
		OLED_ShowString(0,36,"ABC",24,1);//12*24 ��ABC��
	  OLED_Refresh();
		HAL_Delay(500);
		OLED_ScrollDisplay(11,4,1);
}




	//	oled_test();
		//printf("hello\r\n");
		//sr04_getdata();
		//HAL_Delay(3000);
		//HAL_RTC_GetTime(&hrtc,&get_time,RTC_FORMAT_BIN);
		//HAL_RTC_GetDate(&hrtc,&get_data,RTC_FORMAT_BIN);
		//printf("%02d/%02d/%02d/%02d\r\n",2000+get_data.Year,get_data.Month,get_data.Date,get_data.WeekDay);
		//printf("%02d/%02d/%02d\r\n",get_time.Hours,get_time.Minutes,get_time.Seconds);
		//HAL_Delay(1000);
		
		
		//HAL_ADC_Start(&hadc1);   //����ADC
		//HAL_ADC_PollForConversion(&hadc1,10); //�ȴ�ADCת�����
		//adcx = (uint16_t)HAL_ADC_GetValue(&hadc1);   //����adת�����������
		//adcy = (float)adcx*3.3/4096;             //ת��Ϊʵ�ʵ�ѹ
		//printf("volgate = %f\r\n",adcy);
