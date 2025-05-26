#include "model.h"
#include "weights.h"

int8_t model_output = -1;
#define SCALE (pow(2,INPUT_1_OUTPUT_DEC))


typedef enum eModel_Output{
	Unrecognized = -1,
	Zero = 0,
	One = 1,
	Two = 2,
	Three = 3,
	Four = 4,
	Five = 5,
	Six = 6,
	Seven = 7,
	Eight = 8,
	Nine = 9,
}eModel_Output;

#ifdef NNOM_USING_STATIC_MEMORY
	uint8_t static_buf[1024 * 8];
#endif //NNOM_USING_STATIC_MEMORY



Model_State model_state = MODEL_IDLE;

void model_feed_data(void)
{
	const double scale = SCALE;
	uint16_t i = 0;
	for(i = 0; i < IMU_SEQUENCE_LENGTH_MAX;i++){
		nnom_input_data[i*3] = (int8_t)round(IMU_Data_mGyro[i][0] * scale);     //这里单片机推理时使用的应该是加速度值，训练数据时用时前三列值也就是加速度值，之前的推理数据IMU_Data_mGyro是角速度
		nnom_input_data[i*3+1] = (int8_t)round(IMU_Data_mGyro[i][1] * scale);
		nnom_input_data[i*3+2] = (int8_t)round(IMU_Data_mGyro[i][2] * scale);
	}
}


int8_t model_get_output(void)
{
	uint8_t i = 0;
	int8_t max_output = -128;
	int8_t ret = 0;
	for(i = 0; i < 10;i++){
		printf("Output[%d] = %.2f %%\n",i,(nnom_output_data[i] / 127.0)*100);
		if(nnom_output_data[i] >= max_output){
			max_output = nnom_output_data[i] ;
			ret = i;
		}
	}
	if(max_output >= OUPUT_THRESHOLD){
		ret = ret;
	}
	else{
		ret = -1;
	}
	
	switch(ret){
		case Unrecognized:
			printf("Unrecognized");
			break;
		case Zero:
			printf("Zero");
			break;
		case One:
			printf("One");
			break;
		case Two:
			printf("Two");
			break;
		case Three:
			printf("Three");
			break;
		case Four:
			printf("Four");
			break;
		case Five:
			printf("Five");
			break;
		case Six:
			printf("Six");
			break;
		case Seven:
			printf("Seven");
			break;
		case Eight:
			printf("Eight");
			break;
		case Nine:
			printf("Nine");
			break;
	}
	printf("\n");
	return ret;
}

void Model(void *argument)
{
  /* USER CODE BEGIN Model */
  /* Infinite loop */
  #ifdef NNOM_USING_STATIC_MEMORY
	nnom_set_static_buf(static_buf, sizeof(static_buf)); 
  #endif //NNOM_USING_STATIC_MEMORY
  //printf("Model Task Started\r\n");
  uint32_t lastWakeTime = xTaskGetTickCount();
  nnom_model_t* model;
  model = nnom_model_create();
  for(;;)
  {

    vTaskDelayUntil(&lastWakeTime,F2T(RATE_10_HZ));//10hz

    switch(model_state)
        {
            case MODEL_WAIT_DATA:
                if(imu_sample_state == SAMPLE_DONE)
                {
                    model_state = MODEL_RUNNING;
                    printf("采样完成，开始模型推理...\r\n");
                }
                break;

            case MODEL_RUNNING:
                model_feed_data();
                model_run(model);
                model_output = model_get_output();
                model_state = MODEL_DONE;
                break;

            default:
                break;
   // printf("Model Task Running\r\n");
        }
  /* USER CODE END Model */
  }
}
