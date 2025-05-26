#include "config.h"


//********************************************************************************
#ifndef	_IMU_H_
#define	_IMU_H_
#include "CyberryPotter.h"
#include "stm32f4xx_hal.h"
typedef enum {
    SAMPLE_IDLE,     // 空闲状态
    SAMPLE_RUNNING,  // 正在采样
    SAMPLE_DONE     // 采样完成
} IMU_Sample_State;

extern IMU_Sample_State imu_sample_state;
extern uint16_t imu_sample_count;



#define SYSTEM_MODE_DATA_COLLECT 1
#ifdef SYSTEM_MODE_DATA_COLLECT
uint16_t IMU_Data_Print(void);
#endif //SYSTEM_MODE_DATA_COLLECT
void IMU_Sample_Start(void);
void IMU_Get_Data(uint8_t index);
uint8_t IMU_Data_Trans(uint8_t flag);
void IMU_Sample_Start(void);
void IMU_Sample_Stop(void);

#endif	//_IMU_H_
