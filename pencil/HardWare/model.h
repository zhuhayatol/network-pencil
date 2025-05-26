#ifndef _MODEL_H_
#define _MODEL_H_
#include "main.h"

// 添加模型状态枚举
typedef enum {
    MODEL_IDLE,      // 空闲状态
    MODEL_WAIT_DATA, // 等待采样数据
    MODEL_RUNNING,   // 模型运行中
    MODEL_DONE      // 运行完成
} Model_State;
extern Model_State model_state;
int8_t model_get_output(void);
void model_feed_data(void);


#endif // !1#define