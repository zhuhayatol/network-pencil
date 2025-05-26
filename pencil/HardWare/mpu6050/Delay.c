#include "stm32f4xx_hal.h"

/**
  * @brief  寰绾у欢鏃�
  * @param  xus 寤舵椂鏃堕暱锛岃寖鍥达細0~233015
  * @retval 鏃�
  */
void Delay_us(uint32_t us)
{
    uint32_t ticks = us * 168;
    uint32_t start = DWT->CYCCNT;
    while((DWT->CYCCNT - start) < ticks);
}

/**
  * @brief  姣绾у欢鏃�
  * @param  xms 寤舵椂鏃堕暱锛岃寖鍥达細0~4294967295
  * @retval 鏃�
  */
void Delay_ms(uint32_t xms)
{
	while(xms--)
	{
		Delay_us(1000);
	}
}
 
/**
  * @brief  绉掔骇寤舵椂
  * @param  xs 寤舵椂鏃堕暱锛岃寖鍥达細0~4294967295
  * @retval 鏃�
  */
void Delay_s(uint32_t xs)
{
	while(xs--)
	{
		Delay_ms(1000);
	}
} 
