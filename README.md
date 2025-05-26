wait....
# network-pencil
# 代码结构
使用freertos多线程进行多个任务
## 1.83inch屏幕
### 接线
--屏幕----stm32--
-DIN------PA7--SPI-MOSI
-CLK------PA5--SPI-SCK
-CS-------PB6--
-DC-------PA8--
-RST------PA4--
-BL-------PC7--TIM3-->CCR2

--矩阵键盘----stm32--

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


### 代码
存放在HARDWARE下
Show.c
--1.83LCD

Model.c
--模型任务

key_get.c
--矩阵键盘驱动，以及按键控制采样和模型推理

iic.c 
--定义6050引脚

存放在model文件下
weight.h
--训练完的模型参数文件

Serial_Read.py
矩阵键盘按下1，采样150次mpu6050的数据后发送给pc，这里进行数据保存

CNNTrainRaw.py
矩阵键盘按下4，采样150次mpu6050的数据后送给模型推理，并输出结果