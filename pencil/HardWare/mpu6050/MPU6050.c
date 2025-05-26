#include "config.h"
#include "stm32f4xx_hal.h"               // Device header
#include "MPU6050_Reg.h"
#include <stdio.h>
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "IIC.h"

static signed char gyro_orientation[9] = {-1, 0, 0,
                                           0,-1, 0,
                                           0, 0, 1};

static void run_self_test(void)
{
    int result;
    long gyro[3], accel[3];

    result = mpu_run_self_test(gyro, accel);
    if (result == 0x7) {
        /*  Test passed. We can trust the gyro data here, so let's push it down
         * to the DMP.
         */
        float sens;
        unsigned short accel_sens;
        mpu_get_gyro_sens(&sens);
        gyro[0] = (long)(gyro[0] * sens);
        gyro[1] = (long)(gyro[1] * sens);
        gyro[2] = (long)(gyro[2] * sens);
        dmp_set_gyro_bias(gyro);
        mpu_get_accel_sens(&accel_sens);
        accel[0] *= accel_sens;
        accel[1] *= accel_sens;
        accel[2] *= accel_sens;
        dmp_set_accel_bias(accel);
		//printf("setting bias succesfully ......\r\n");
    }
}

static  unsigned short inv_row_2_scale(const signed char *row)
{
    unsigned short b;

    if (row[0] > 0)
        b = 0;
    else if (row[0] < 0)
        b = 4;
    else if (row[1] > 0)
        b = 1;
    else if (row[1] < 0)
        b = 5;
    else if (row[2] > 0)
        b = 2;
    else if (row[2] < 0)
        b = 6;
    else
        b = 7;      // error
    return b;
}

static  unsigned short inv_orientation_matrix_to_scalar(const signed char *mtx)
{
	unsigned short scalar;
	scalar = inv_row_2_scale(mtx);
	scalar |= inv_row_2_scale(mtx + 3) << 3;
	scalar |= inv_row_2_scale(mtx + 6) << 6;


	return scalar;
}

int MPU6050_Init(void)
{
    IIC_Init();
    
    // 1. 添加延时确保电源稳定
    HAL_Delay(100);
    
    // 2. 检查设备ID
    unsigned char temp[1] = {0};
    if(IIC_read(0x68, MPU6050_RA_WHO_AM_I, 1, temp) != 0 || temp[0] != 0x68) {
        printf("MPU6050 ID check failed!\r\n");
        return -1;
    }
    

    
    // 4. 初始化DMP
    struct int_param_s int_param = {0}; // 正确初始化结构体
    
    if(mpu_init(&int_param) != 0) {
        printf("MPU init failed!\r\n");
        return -1;
    }
    
    // 5. 配置传感器
    if(mpu_set_sensors(INV_XYZ_GYRO | INV_XYZ_ACCEL) != 0) {
        printf("Set sensors failed!\r\n");
        return -1;
    }
    
    // 6. 配置FIFO
    if(mpu_configure_fifo(INV_XYZ_GYRO | INV_XYZ_ACCEL) != 0) {
        printf("Configure FIFO failed!\r\n");
        return -1;
    }
    
    // 7. 设置采样率
    if(mpu_set_sample_rate(IMU_DEFAULT_HZ) != 0) {
        printf("Set sample rate failed!\r\n");
        return -1;
    }
    
    // 8. 加载并配置DMP
    if(dmp_load_motion_driver_firmware() != 0) {
        printf("Load DMP firmware failed!\r\n");
        return -1;
    }
    
    if(dmp_set_orientation(inv_orientation_matrix_to_scalar(gyro_orientation)) != 0) {
        printf("Set DMP orientation failed!\r\n");
        return -1;
    }
    
    // 9. 启用DMP功能
    if(dmp_enable_feature(DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_TAP |
        DMP_FEATURE_ANDROID_ORIENT | DMP_FEATURE_SEND_RAW_ACCEL | 
        DMP_FEATURE_SEND_CAL_GYRO | DMP_FEATURE_GYRO_CAL) != 0) {
        printf("Enable DMP features failed!\r\n");
        return -1;
    }
    
    // 10. 设置DMP输出速率
    if(dmp_set_fifo_rate(IMU_DEFAULT_HZ) != 0) {
        printf("Set DMP FIFO rate failed!\r\n");
        return -1;
    }
    
    // 11. 运行自检
    run_self_test();
    
    // 12. 配置最终参数
    mpu_set_dmp_state(1);  // 启用DMP
    mpu_set_accel_fsr(4);  // 设置加速度量程为±4g
    mpu_set_gyro_fsr(500); // 设置陀螺仪量程为±500dps
    
    printf("MPU6050 initialization complete!\r\n");

	return 0;
}


