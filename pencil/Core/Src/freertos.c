/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
typedef StaticTask_t osStaticThreadDef_t;
typedef StaticQueue_t osStaticMessageQDef_t;
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for Mpu6050Task */
osThreadId_t Mpu6050TaskHandle;
uint32_t Mpu6050TaskBuffer[ 128 ];
osStaticThreadDef_t Mpu6050TaskControlBlock;
const osThreadAttr_t Mpu6050Task_attributes = {
  .name = "Mpu6050Task",
  .cb_mem = &Mpu6050TaskControlBlock,
  .cb_size = sizeof(Mpu6050TaskControlBlock),
  .stack_mem = &Mpu6050TaskBuffer[0],
  .stack_size = sizeof(Mpu6050TaskBuffer),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for ShowTask */
osThreadId_t ShowTaskHandle;
uint32_t ShowTaskBuffer[  512 ];
osStaticThreadDef_t ShowTaskControlBlock;
const osThreadAttr_t ShowTask_attributes = {
  .name = "ShowTask",
  .cb_mem = &ShowTaskControlBlock,
  .cb_size = sizeof(ShowTaskControlBlock),
  .stack_mem = &ShowTaskBuffer[0],
  .stack_size = sizeof(ShowTaskBuffer),
  .priority = (osPriority_t) osPriorityHigh1,
};
/* Definitions for DataTransTask */
osThreadId_t DataTransTaskHandle;
uint32_t DataTransTaskBuffer[ 128 ];
osStaticThreadDef_t DataTransTaskControlBlock;
const osThreadAttr_t DataTransTask_attributes = {
  .name = "DataTransTask",
  .cb_mem = &DataTransTaskControlBlock,
  .cb_size = sizeof(DataTransTaskControlBlock),
  .stack_mem = &DataTransTaskBuffer[0],
  .stack_size = sizeof(DataTransTaskBuffer),
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for DataGetTask */
osThreadId_t DataGetTaskHandle;
uint32_t DataGetTaskBuffer[ 128 ];
osStaticThreadDef_t DataGetTaskControlBlock;
const osThreadAttr_t DataGetTask_attributes = {
  .name = "DataGetTask",
  .cb_mem = &DataGetTaskControlBlock,
  .cb_size = sizeof(DataGetTaskControlBlock),
  .stack_mem = &DataGetTaskBuffer[0],
  .stack_size = sizeof(DataGetTaskBuffer),
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for ModelTask */
osThreadId_t ModelTaskHandle;
uint32_t ModelTaskBuffer[ 512 ];
osStaticThreadDef_t ModelTaskControlBlock;
const osThreadAttr_t ModelTask_attributes = {
  .name = "ModelTask",
  .cb_mem = &ModelTaskControlBlock,
  .cb_size = sizeof(ModelTaskControlBlock),
  .stack_mem = &ModelTaskBuffer[0],
  .stack_size = sizeof(ModelTaskBuffer),
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Mpu6050Queue */
osMessageQueueId_t Mpu6050QueueHandle;
uint8_t Mpu6050QueueBuffer[ 3 * sizeof( uint16_t ) ];
osStaticMessageQDef_t Mpu6050QueueControlBlock;
const osMessageQueueAttr_t Mpu6050Queue_attributes = {
  .name = "Mpu6050Queue",
  .cb_mem = &Mpu6050QueueControlBlock,
  .cb_size = sizeof(Mpu6050QueueControlBlock),
  .mq_mem = &Mpu6050QueueBuffer,
  .mq_size = sizeof(Mpu6050QueueBuffer)
};
/* Definitions for ModelgetQueue */
osMessageQueueId_t ModelgetQueueHandle;
uint8_t ModelgetQueueBuffer[ 10 * sizeof( uint16_t ) ];
osStaticMessageQDef_t ModelgetQueueControlBlock;
const osMessageQueueAttr_t ModelgetQueue_attributes = {
  .name = "ModelgetQueue",
  .cb_mem = &ModelgetQueueControlBlock,
  .cb_size = sizeof(ModelgetQueueControlBlock),
  .mq_mem = &ModelgetQueueBuffer,
  .mq_size = sizeof(ModelgetQueueBuffer)
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */


void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of Mpu6050Queue */
  Mpu6050QueueHandle = osMessageQueueNew (3, sizeof(uint16_t), &Mpu6050Queue_attributes);

  /* creation of ModelgetQueue */
  ModelgetQueueHandle = osMessageQueueNew (10, sizeof(uint16_t), &ModelgetQueue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of Mpu6050Task */
  Mpu6050TaskHandle = osThreadNew(Mpu6050, NULL, &Mpu6050Task_attributes);

  /* creation of ShowTask */
  ShowTaskHandle = osThreadNew(Show, NULL, &ShowTask_attributes);

  /* creation of DataTransTask */
  DataTransTaskHandle = osThreadNew(DataTrans, NULL, &DataTransTask_attributes);

  /* creation of DataGetTask */
  DataGetTaskHandle = osThreadNew(DataGet, NULL, &DataGetTask_attributes);

  /* creation of ModelTask */
  ModelTaskHandle = osThreadNew(Model, NULL, &ModelTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_Mpu6050 */
/**
  * @brief  Function implementing the Mpu6050Task thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_Mpu6050 */
void Mpu6050(void *argument)
{
  /* USER CODE BEGIN Mpu6050 */
  /* Infinite loop */

  uint32_t lastWakeTime = xTaskGetTickCount();
  for(;;)
  {
    vTaskDelayUntil(&lastWakeTime,F2T(RATE_10_HZ));
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);

  }
  /* USER CODE END Mpu6050 */
}

/* USER CODE BEGIN Header_Show */
/**
* @brief Function implementing the ShowTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Show */
// void Show(void *argument)
// {
//   /* USER CODE BEGIN Show */
//   /* Infinite loop */
//   for(;;)
//   {

//   }
//   /* USER CODE END Show */
// }

/* USER CODE BEGIN Header_DataTrans */
/**
* @brief Function implementing the DataTransTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_DataTrans */
void DataTrans(void *argument)
{
  /* USER CODE BEGIN DataTrans */
  /* Infinite loop */
  uint32_t lastWakeTime = xTaskGetTickCount();
  for(;;)
  {
    vTaskDelayUntil(&lastWakeTime,F2T(RATE_10_HZ));//50hz的任务频率
  }
  /* USER CODE END DataTrans */
}

/* USER CODE BEGIN Header_DataGet */
/**
* @brief Function implementing the DataGetTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_DataGet */
void DataGet(void *argument)
{
  /* USER CODE BEGIN DataGet */
  /* Infinite loop */
  uint32_t lastWakeTime = xTaskGetTickCount();
  for(;;)
  {
    vTaskDelayUntil(&lastWakeTime,F2T(RATE_10_HZ));//50hz的任务频率

  }
  /* USER CODE END DataGet */
}

/* USER CODE BEGIN Header_Model */
/**
* @brief Function implementing the ModelTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Model */
void Model(void *argument)
{
  /* USER CODE BEGIN Model */
  /* Infinite loop */
  uint32_t lastWakeTime = xTaskGetTickCount();
  for(;;)
  {
    vTaskDelayUntil(&lastWakeTime,F2T(RATE_10_HZ));//50hz的任务频率
  }
  /* USER CODE END Model */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

