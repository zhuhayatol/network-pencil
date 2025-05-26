#include "key_get.h"

/*˵��
    ���Ŷ�Ӧ
    PE8  ROW4
    PE10 ROW3
    PE12 ROW2
    PE14 ROW1
    
    PE9  COL1
    PE11 COL2
    PE13 COL3
    PE15 COL4
     
ɨ��ԭ��
    - ��ʼ״̬
        - ��������Ĭ��Ϊ�ߵ�ƽ
        - ��������ͨ���������豣�ָߵ�ƽ
    - ɨ�����
        - ���ν�ÿһ������
        - ��ȡ�����еĵ�ƽ״̬
        - ���ĳ��Ϊ�͵�ƽ��˵�����и��н��洦�İ���������
*/

//���尴��ֵ
const uint16_t KeyMatrix[4][4] = {
    {16, 15, 14, 13},
    {12, 11, 10, 9},
    {8, 7, 6, 5},
    {4, 3, 2, 1},
};

uint16_t key = 0; //��ǰ����ֵ

void Key_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOE_CLK_ENABLE();

    //��ʼ��������
    GPIO_InitStruct.Pin = ROW1 | ROW2 | ROW3 | ROW4;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

    //��ʼ��������
    GPIO_InitStruct.Pin = COL1 | COL2 | COL3 | COL4;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

}

//����ĳһ��Ϊ�͵�ƽ
void SetRowLow(uint16_t row)
{
    //��������������Ϊ�ߵ�ƽ
    HAL_GPIO_WritePin(GPIOE, ROW1 | ROW2 | ROW3 | ROW4, GPIO_PIN_SET);
    //��ָ����������Ϊ�͵�ƽ
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

//��ȡ����״̬
uint16_t ReadColumnState(void)
{
    uint16_t colState = 0;
    //��ȡ����״̬
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
    static uint16_t keyValue = 0;        // ��ǰ����ֵ
    static uint16_t last_keyValue = 0;   // �ϴΰ���ֵ
    static uint8_t key_state = 0;        // ����״̬��0-δ���£�1-�Ѱ���

    for (uint8_t row = 1; row <= 4; row++)
    {
        SetRowLow(row);
        uint16_t colState = ReadColumnState();
        
        if (colState != 0)  // �а���������
        {
            if (key_state == 0)  // ֮ǰδ����
            {
                keyValue = KeyMatrix[row - 1][colState - 1];
                if (keyValue != last_keyValue)  // ��ͬ����
                {
                    //printf("Key pressed: %d\r\n", keyValue);
                    last_keyValue = keyValue;
                }
                key_state = 1;  // ��ǰ���״̬
            }
            return last_keyValue;
        }
    }
    
    // û�а���������
    key_state = 0;  // �������״̬
    return last_keyValue;
}

// �ڰ�����������
void Key_Process(void)
{
    static uint16_t last_key_state = 0;  // ��һ�ΰ���״̬
    uint16_t key_value = Key_Get();
    
    if(key_value == 1)  // ����1������
    {
        if(last_key_state == 0)  // ֮ǰδ����
        {
            if(imu_sample_state != SAMPLE_RUNNING)
            {
                IMU_Sample_Start();
            }
        }
        last_key_state = 1;  // ��¼����״̬
    }
    else if(key_value == 4)  // ����4������������
    {
        if(last_key_state == 0)  // ֮ǰδ����
        {
            if(imu_sample_state != SAMPLE_RUNNING && (model_state == MODEL_IDLE || model_state))
            {
                // ��ʼ�µĲ���
                model_state = MODEL_WAIT_DATA;
                IMU_Sample_Start();
                printf("��ʼ����...\r\n");
            }
        }
        last_key_state = 1;  // ��¼����״̬
    }
    else 
    {
        last_key_state = 0;  // �����ͷţ����״̬
    }
}