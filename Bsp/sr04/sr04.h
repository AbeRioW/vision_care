#ifndef __SR04_H
#define __SR04_H

#include "tim.h"
#include "stdio.h"
#include "gpio.h"
#include "stdbool.h"
#include "stdint.h"


extern uint8_t distance_legth;  //Ĭ�ϵľ���ֵ
extern bool distance_boundary;

#define TRIG_H    HAL_GPIO_WritePin(Trig_GPIO_Port, Trig_Pin, GPIO_PIN_SET);
#define TRIG_L    HAL_GPIO_WritePin(Trig_GPIO_Port, Trig_Pin, GPIO_PIN_RESET);

void delay_us(uint32_t us);
void sr04_getdata(void);


#endif
