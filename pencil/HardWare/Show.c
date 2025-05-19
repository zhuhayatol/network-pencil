#include "show.h"
#include "DEV_Config.h"//引脚修改
#include <stdint.h>
#include "LCD_1in83.h"//该文件作用是给出了LCD_1in83的相关函数和定义
#include "GUI_Paint.h"//该文件作用是使用GUI_Paint库来绘制图形和文字
#include "Debug.h"//该文件作用是调试输出
#include "main.h"//该文件作用是包含主函数和其他必要的头文件
#include "image.h"//该文件作用是包含图像数据
#include "cmsis_os.h" // 添加FreeRTOS头文件

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

  	while(1)
    {
        vTaskDelayUntil(&lastWakeTime,F2T(RATE_1000_HZ));//50hz的任务频率

       
        Paint_DrawRectangle(125, 10, 225, 58, RED     ,DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
        Paint_DrawLine  (125, 10, 225, 58,    MAGENTA ,DOT_PIXEL_2X2,LINE_STYLE_SOLID);
        Paint_DrawLine  (225, 10, 125, 58,    MAGENTA ,DOT_PIXEL_2X2,LINE_STYLE_SOLID);
        Paint_DrawCircle(150,100,  25,        BLUE    ,DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
        Paint_DrawCircle(180,100,  25,        BLACK   ,DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
        Paint_DrawCircle(210,100,  25,        RED     ,DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
        Paint_DrawCircle(165,125,  25,        YELLOW  ,DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
        Paint_DrawCircle(195,125,  25,        GREEN   ,DOT_PIXEL_2X2,DRAW_FILL_EMPTY);


    }

}
