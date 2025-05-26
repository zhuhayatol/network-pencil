/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Show.h"
#include "cmsis_os.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "hardware.h"
#include "IIC.h"
#include "MPU6050_Reg.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "MPU6050.h"
#include "mpu6050get.h"
#include "IMU.h"
#include "FreeRTOS.h"
#include "config.h"
#include "CyberryPotter.h"
#include "MPU6050get.h"
#include "key_get.h"
#include "model.h"
#include "nnom.h"
#include "task.h"

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
#define RATE_1_HZ		  1
#define RATE_5_HZ		  5
#define RATE_10_HZ		10
#define RATE_20_HZ		20
#define RATE_25_HZ		25
#define RATE_50_HZ		50
#define RATE_100_HZ		100
#define RATE_200_HZ 	200
#define RATE_250_HZ 	250
#define RATE_500_HZ 	500
#define RATE_1000_HZ 	1000

#define M2T(X) ((unsigned int)((X)*(configTICK_RATE_HZ/1000.0)))
#define F2T(X) ((unsigned int)((configTICK_RATE_HZ/(X))))
/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
void Mpu6050(void *argument);
void Show(void *argument);
void DataTrans(void *argument);
void DataGet(void *argument);
void Model(void *argument);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Key_Pin GPIO_PIN_0
#define Key_GPIO_Port GPIOA
#define RST_Pin GPIO_PIN_4
#define RST_GPIO_Port GPIOA
#define LED_Pin GPIO_PIN_2
#define LED_GPIO_Port GPIOB
#define DC_Pin GPIO_PIN_8
#define DC_GPIO_Port GPIOA
#define CS_Pin GPIO_PIN_6
#define CS_GPIO_Port GPIOB
// Ìí¼ÓÄ£ÐÍ×´Ì¬Ã¶¾Ù

/* USER CODE BEGIN Private defines */
extern float IMU_Data_mGyro[IMU_SEQUENCE_LENGTH_MAX][3];
extern float IMU_Data_mAcc[IMU_SEQUENCE_LENGTH_MAX][3];
extern uint16_t key;//ï¿½ï¿½Ç°ï¿½ï¿½ï¿½ï¿½Öµ
extern uint16_t imu_sample_count;//ï¿½ï¿½Ç°ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
