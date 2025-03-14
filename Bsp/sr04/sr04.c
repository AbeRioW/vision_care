#include "sr04.h"
#include "oled.h"



float distant;     									//��������
uint32_t measure_buf[3] = {0};			//��Ŷ�ʱ������ֵ������
uint8_t measure_cnt = 0;  				  //״̬��־λ
uint32_t higt_time;                 //������ģ�鷵�ظߵ�ƽʱ��


uint8_t distance_legth = 5;  //Ĭ�ϵľ���ֵ
bool distance_boundary = false;

//us��ʱ����
void delay_us(uint32_t us)
{
		uint32_t delay = (HAL_RCC_GetHCLKFreq()/4000000*us);
	  while(delay--);
}

//��ȡ����
void sr04_getdata(void)
{
	  char long_dis[100]={0};
		switch(measure_cnt)
		{
			case 0:
				TRIG_H;
			  delay_us(30);
			  TRIG_L;
			
			  measure_cnt++;
			  __HAL_TIM_SET_CAPTUREPOLARITY(&htim2,TIM_CHANNEL_1,TIM_INPUTCHANNELPOLARITY_RISING);
				HAL_TIM_IC_Start_IT(&htim2,TIM_CHANNEL_1);      //�������벶��
				break;
			case 3:
				 higt_time = measure_buf[1]-measure_buf[0];      //�ߵ�ƽʱ��
			  
			   distant = (higt_time*0.034)/2;                	//��λ��cm
			
//			   sprintf(long_dis,"%.2f",distant);
//			   OLED_ShowString(90,0,(uint8_t*)long_dis,16,1);  //����ʱ�ɴ�Һ����ʾ
			   OLED_Refresh(); 
			
			  if(distant <=distance_legth) 
				{
						distance_boundary = true;
				}
			  measure_cnt = 0;
			  TIM2->CNT = 0;                //�����ʱ������
				HAL_TIM_IC_Stop_IT(&htim2,TIM_CHANNEL_1);
			
			  break;
		}
}

//�ص�����
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
		if(TIM2==htim->Instance)    //�жϴ������жϵĶ�ʱ��ΪTIM2
		{
				switch(measure_cnt)
				{
					case 1:
							measure_buf[0] = HAL_TIM_ReadCapturedValue(&htim2,TIM_CHANNEL_1);     //��ȡ��ǰ�Ĳ���ֵ
					    __HAL_TIM_SET_CAPTUREPOLARITY(&htim2,TIM_CHANNEL_1,TIM_INPUTCHANNELPOLARITY_FALLING);         //����Ϊ�½��ز���
							measure_cnt++;
					break;
					
					case 2:
							measure_buf[1] = HAL_TIM_ReadCapturedValue(&htim2,TIM_CHANNEL_1);     //��ȡ��ǰ�Ĳ���ֵ
					    HAL_TIM_IC_Stop_IT(&htim2,TIM_CHANNEL_1);                             //ֹͣ����
					    measure_cnt++;
					break;
				}
		}
}

