#include "show.h"
#include "DEV_Config.h"//引脚修改
#include <stdint.h>
#include "LCD_1in83.h"//该文件作用是给出了LCD_1in83的相关函数和定义
#include "GUI_Paint.h"//该文件作用是使用GUI_Paint库来绘制图形和文字
#include "Debug.h"//该文件作用是调试输出
#include "main.h"//该文件作用是包含主函数和其他必要的头文件
#include "image.h"//该文件作用是包含图像数据
#include "cmsis_os.h" // 添加FreeRTOS头文件


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

  	Paint_DrawString_CN(50,180, "你好",   &Font24CN,WHITE,  RED);
    Paint_DrawImage(gImage_1,25,70,60,60);

    

  	uint32_t lastWakeTime = xTaskGetTickCount();
   //printf("Show Task Started\r\n");

  	while(1)
    {
        vTaskDelayUntil(&lastWakeTime,F2T(RATE_50_HZ));//50hz的任务频率
        //printf("Show Task Running\r\n");

        Paint_DrawFloatNum(130, 20 ,IMU_Data_mAcc[0][0], 3, &Font20,  WHITE,  BLACK);
        Paint_DrawFloatNum(130, 90 ,IMU_Data_mAcc[0][1], 3, &Font20,  WHITE,  BLACK);
        Paint_DrawFloatNum(130, 160 ,IMU_Data_mAcc[0][2], 3, &Font20,  WHITE,  BLACK);


        show_board();
    }

}

//展示按键值
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
