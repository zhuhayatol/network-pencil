#include "mpu6050get.h"
#include "IMU.h"




void Mpu6050(void *argument)
{
  /* USER CODE BEGIN Mpu6050 */
  /* Infinite loop */
  //printf("Mpu6050 Task Started\r\n");
  uint32_t lastWakeTime = xTaskGetTickCount();
  vTaskDelay(pdMS_TO_TICKS(100));
  for(;;)
  {
    vTaskDelayUntil(&lastWakeTime,F2T(RATE_20_HZ));

    //HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
    //printf("Mpu6050 Task Running\r\n");

  }
  /* USER CODE END Mpu6050 */
}


//按键按下后才开始读取imu数据，读满IMU_SEQUENCE_LENGTH_MAX后读取停止
void mpu6050_sample(void)
{
  static uint8_t sample = 0;
  static uint8_t sample_flag = 0;

  sample = Key_Get();
  if(sample == 1 && sample_flag == 0)
  {
    sample_flag = 1;
    
  
  }



}