#include "key_get.h"

/*说明
    引脚对应
    PE8  ROW4
    PE10 ROW3
    PE12 ROW2
    PE14 ROW1
    
    PE9  COL1
    PE11 COL2
    PE13 COL3
    PE15 COL4
     
扫描原理
    - 初始状态
        - 所有行线默认为高电平
        - 所有列线通过上拉电阻保持高电平
    - 扫描过程
        - 依次将每一行拉低
        - 读取所有列的电平状态
        - 如果某列为低电平，说明该行该列交叉处的按键被按下
*/

//定义按键值
const uint16_t KeyMatrix[4][4] = {
    {16, 15, 14, 13},
    {12, 11, 10, 9},
    {8, 7, 6, 5},
    {4, 3, 2, 1},
};

uint16_t key = 0; //当前按键值

void Key_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOE_CLK_ENABLE();

    //初始化行引脚
    GPIO_InitStruct.Pin = ROW1 | ROW2 | ROW3 | ROW4;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    //初始化列引脚
    GPIO_InitStruct.Pin = COL1 | COL2 | COL3 | COL4;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

}

//设置某一行为低电平
void SetRowLow(uint16_t row)
{
    //将所有行线设置为高电平
    HAL_GPIO_WritePin(GPIOE, ROW1 | ROW2 | ROW3 | ROW4, GPIO_PIN_SET);
    //将指定行线设置为低电平
    switch (row)
    {
        case 1:
            HAL_GPIO_WritePin(GPIOE, ROW1, GPIO_PIN_RESET);
            break;
        case 2:
            HAL_GPIO_WritePin(GPIOE, ROW2, GPIO_PIN_RESET);
            break;
        case 3:
            HAL_GPIO_WritePin(GPIOE, ROW3, GPIO_PIN_RESET);
            break;
        case 4:
            HAL_GPIO_WritePin(GPIOE, ROW4, GPIO_PIN_RESET);
            break;
        default:
            break;
    }
}

//读取列线状态
uint16_t ReadColumnState(void)
{
    uint16_t colState = 0;
    //读取列线状态
    if (HAL_GPIO_ReadPin(GPIOE, COL1) == GPIO_PIN_RESET)
        colState = 1;
    if (HAL_GPIO_ReadPin(GPIOE, COL2) == GPIO_PIN_RESET)
        colState = 2;
    if (HAL_GPIO_ReadPin(GPIOE, COL3) == GPIO_PIN_RESET)
        colState = 3;
    if (HAL_GPIO_ReadPin(GPIOE, COL4) == GPIO_PIN_RESET)
        colState = 4;

    return colState;
}

uint16_t Key_Get(void)
{
    static uint16_t keyValue = 0;        // 当前按键值
    static uint16_t last_keyValue = 0;   // 上次按键值
    static uint8_t key_state = 0;        // 按键状态：0-未按下，1-已按下

    for (uint8_t row = 1; row <= 4; row++)
    {
        SetRowLow(row);
        uint16_t colState = ReadColumnState();
        
        if (colState != 0)  // 有按键被按下
        {
            if (key_state == 0)  // 之前未按下
            {
                keyValue = KeyMatrix[row - 1][colState - 1];
                if (keyValue != last_keyValue)  // 不同按键
                {
                    //printf("Key pressed: %d\r\n", keyValue);
                    last_keyValue = keyValue;
                }
                key_state = 1;  // 标记按下状态
            }
            return last_keyValue;
        }
    }
    
    // 没有按键被按下
    key_state = 0;  // 清除按下状态
    return last_keyValue;
}

// 在按键处理函数中
void Key_Process(void)
{
    static uint16_t last_key_state = 0;  // 上一次按键状态
    uint16_t key_value = Key_Get();
    
    if(key_value == 1)  // 按键1被按下
    {
        if(last_key_state == 0)  // 之前未按下
        {
            if(imu_sample_state != SAMPLE_RUNNING)
            {
                IMU_Sample_Start();
            }
        }
        last_key_state = 1;  // 记录按下状态
    }
    else if(key_value == 4)  // 按键4控制整个流程
    {
        if(last_key_state == 0)  // 之前未按下
        {
            if(imu_sample_state != SAMPLE_RUNNING && (model_state == MODEL_IDLE || model_state))
            {
                // 开始新的采样
                model_state = MODEL_WAIT_DATA;
                IMU_Sample_Start();
                printf("开始采样...\r\n");
            }
        }
        last_key_state = 1;  // 记录按下状态
    }
    else 
    {
        last_key_state = 0;  // 按键释放，清除状态
    }
}