#include "stm32f4xx_hal.h"

/**
  * @brief  微秒级延旄1�7
  * @param  xus 延时时长，范围：0~233015
  * @retval 旄1�7
  */
void Delay_us(uint32_t us)
{
    uint32_t ticks = us * 168;
    uint32_t start = DWT->CYCCNT;
    while((DWT->CYCCNT - start) < ticks);
}

/**
  * @brief  毫秒级延旄1�7
  * @param  xms 延时时长，范围：0~4294967295
  * @retval 旄1�7
  */
void Delay_ms(uint32_t xms)
{
	while(xms--)
	{
		Delay_us(1000);
	}
}
 
/**
  * @brief  秒级延时
  * @param  xs 延时时长，范围：0~4294967295
  * @retval 旄1�7
  */
void Delay_s(uint32_t xs)
{
	while(xs--)
	{
		Delay_ms(1000);
	}
} 
