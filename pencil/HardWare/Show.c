#include "show.h"
#include "DEV_Config.h"//�����޸�
#include <stdint.h>
#include "LCD_1in83.h"//���ļ������Ǹ�����LCD_1in83����غ����Ͷ���
#include "GUI_Paint.h"//���ļ�������ʹ��GUI_Paint��������ͼ�κ�����
#include "Debug.h"//���ļ������ǵ������
#include "main.h"//���ļ������ǰ�����������������Ҫ��ͷ�ļ�
#include "image.h"//���ļ������ǰ���ͼ������
#include "cmsis_os.h" // ���FreeRTOSͷ�ļ�


void show_board(void);

void Show(void *argument)
{

    printf("LCD_1IN83 Demo\r\n");
    DEV_Module_Init();

    printf("LCD_1IN83_ Init and Clear...\r\n");
    LCD_1IN83_SetBackLight(1000);
    LCD_1IN83_Init(HORIZONTAL);
    LCD_1IN83_Clear(WHITE);
    

    printf("Paint_NewImage\r\n");
    Paint_NewImage(LCD_1IN83_WIDTH, LCD_1IN83_HEIGHT, 0, WHITE);

    printf("Set Clear and Display Funtion\r\n");
    Paint_SetClearFuntion(LCD_1IN83_Clear);
    Paint_SetDisplayFuntion(LCD_1IN83_DrawPoint);

    printf("Paint_Clear\r\n");
    Paint_Clear(WHITE);
    DEV_Delay_ms(100);

    printf("drawing...\r\n");

    Paint_DrawString_EN(30, 10, "123", &Font24, YELLOW, RED);  
    Paint_DrawString_EN(30, 34, "ABC", &Font24, BLUE, CYAN);
  	Paint_DrawFloatNum (30, 58 ,987.652, 3, &Font12,  WHITE,  BLACK);

  	Paint_DrawString_CN(50,180, "���",   &Font24CN,WHITE,  RED);
    Paint_DrawImage(gImage_1,25,70,60,60);

    

  	uint32_t lastWakeTime = xTaskGetTickCount();
   //printf("Show Task Started\r\n");

  	while(1)
    {
        vTaskDelayUntil(&lastWakeTime,F2T(RATE_50_HZ));//50hz������Ƶ��
        //printf("Show Task Running\r\n");

        Paint_DrawFloatNum(130, 20 ,IMU_Data_mAcc[0][0], 3, &Font20,  WHITE,  BLACK);
        Paint_DrawFloatNum(130, 90 ,IMU_Data_mAcc[0][1], 3, &Font20,  WHITE,  BLACK);
        Paint_DrawFloatNum(130, 160 ,IMU_Data_mAcc[0][2], 3, &Font20,  WHITE,  BLACK);


        show_board();
    }

}

//չʾ����ֵ
void show_board(void)
{
      static uint16_t board = 0;
      static uint16_t last_board = 0;
        board = Key_Get();
        
        if (last_board != board)
        {
           Paint_ClearWindows(130, 190, 200, 210, WHITE); 
        }
        last_board = board;

        Paint_DrawNum(130, 190 ,board,  &Font20,  WHITE,  BLACK);
}
