wait....
# network-pencil
# ����ṹ
ʹ��freertos���߳̽��ж������
## 1.83inch��Ļ
### ����
--��Ļ----stm32--
-DIN------PA7--SPI-MOSI
-CLK------PA5--SPI-SCK
-CS-------PB6--
-DC-------PA8--
-RST------PA4--
-BL-------PC7--TIM3-->CCR2

--�������----stm32--

#define ROW1 GPIO_PIN_14
#define ROW2 GPIO_PIN_12
#define ROW3 GPIO_PIN_10
#define ROW4 GPIO_PIN_8
#define COL1 GPIO_PIN_9
#define COL2 GPIO_PIN_11
#define COL3 GPIO_PIN_13
#define COL4 GPIO_PIN_15

--mou6050----stm32--

#define IIC_SDA(BitVal) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, (BitVal) ? GPIO_PIN_SET : GPIO_PIN_RESET)
#define IIC_SCL(BitVal) HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, (BitVal) ? GPIO_PIN_SET : GPIO_PIN_RESET);


### ����
�����HARDWARE��
Show.c
--1.83LCD

Model.c
--ģ������

key_get.c
--��������������Լ��������Ʋ�����ģ������

iic.c 
--����6050����

�����model�ļ���
weight.h
--ѵ�����ģ�Ͳ����ļ�

Serial_Read.py
������̰���1������150��mpu6050�����ݺ��͸�pc������������ݱ���

CNNTrainRaw.py
������̰���4������150��mpu6050�����ݺ��͸�ģ��������������