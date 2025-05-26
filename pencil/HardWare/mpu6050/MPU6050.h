#ifndef __MPU6050_H
#define __MPU6050_H

#include "stm32f4xx_hal.h"                    // Device header

int MPU6050_Init(void); 
void DMP_Init(void);
void Read_DMP(void);

#endif
