#ifndef KEY_GET_H
#define KEY_GET_H

#include "main.h"



//定义行列引脚
#define ROW1 GPIO_PIN_14
#define ROW2 GPIO_PIN_12
#define ROW3 GPIO_PIN_10
#define ROW4 GPIO_PIN_8
#define COL1 GPIO_PIN_9
#define COL2 GPIO_PIN_11
#define COL3 GPIO_PIN_13
#define COL4 GPIO_PIN_15




uint16_t Key_Get(void);
uint16_t ReadColumnState(void);
void SetRowLow(uint16_t row);
void Key_Init(void);
void Key_Process(void);
#endif // DEBU;