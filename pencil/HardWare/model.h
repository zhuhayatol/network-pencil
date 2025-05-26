#ifndef _MODEL_H_
#define _MODEL_H_
#include "main.h"

// ���ģ��״̬ö��
typedef enum {
    MODEL_IDLE,      // ����״̬
    MODEL_WAIT_DATA, // �ȴ���������
    MODEL_RUNNING,   // ģ��������
    MODEL_DONE      // �������
} Model_State;
extern Model_State model_state;
int8_t model_get_output(void);
void model_feed_data(void);


#endif // !1#define