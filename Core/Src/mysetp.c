#include "mysetp.h"
#include "oled.h"


extern TIM_HandleTypeDef htim2;
extern UART_HandleTypeDef huart1;
uint8_t dds[]={11,22};


u8g2_t u8g2;

unsigned char bmp[]=
{
0xF8,0x0F,0x08,0x08,0x08,0x08,0xF8,0x0F,0x08,0x08,0x08,0x08,0xF8,0x0F,0x00,0x00,0xFF,0x7F,0x80,0x00,0x88,0x00,0x88,0x1F,0x88,0x00,0x94,0x00,0xA2,0x00,0xC1,0x7F,
0x40,0x00,0x40,0x00,0xE0,0x0F,0x10,0x04,0x1C,0x02,0x20,0x01,0xC0,0x02,0x30,0x01,0x8E,0x1F,0x40,0x10,0x30,0x08,0x4C,0x04,0x80,0x02,0x80,0x01,0x70,0x00,0x0E,0x00,
0x80,0x00,0x80,0x00,0x80,0x00,0x90,0x04,0x90,0x08,0x88,0x10,0x88,0x20,0x84,0x28,0x82,0x08,0x80,0x04,0x00,0x02,0x00,0x01,0x80,0x00,0x40,0x00,0x30,0x00,0x0E,0x00};
unsigned char mydist=40;
char flag=1;


    int num = 7;
    char str[25];

void mysetp(){
    //oledINIT(mhi2c);
    u8g2Init(&u8g2);
    HAL_TIM_Base_Start_IT(&htim2);//使能定时器中断


     itoa(num, str, 10);

     HAL_UART_Transmit_DMA(&huart1,(uint8_t *)str,3);

    while (1)
    {
        
       // HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
     /*
        u8g2_SetFont(&u8g2, u8g2_font_6x13_tr  );
        u8g2_DrawCircle(&u8g2,64,mydist,10,U8G2_DRAW_ALL);
        u8g2_DrawStr(&u8g2,0,10,"Neotoxic: me@qvqol.cn");
        u8g2_DrawLine(&u8g2,10,60,118,60);
        u8g2_DrawLine(&u8g2,10,20,10,60);
        //u8g2_DrawXBM(&u8g2,12,10,16,48,bmp);
        u8g2_SendBuffer(&u8g2);
        HAL_Delay(10);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
        HAL_Delay(10);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
    
        if (flag)
        {
           if (mydist>35)
           mydist+=2;
           else
           mydist+=1;
   
           if (mydist>49)
             flag=0;
        }else{
        if (mydist>35)
           mydist-=2;
           else
           mydist-=1;
           if (mydist<21)
             flag=1;
        }
        u8g2_ClearBuffer(&u8g2);*/

        num++;
        itoa(num, str, 10);

        
        
        HAL_Delay(500);
     
    }
    
    


}

int fputc(int ch,FILE *f){
    //HAL_UART_Transmit(&huart1,(uint8_t *)&ch,1,1000);
    //HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
    return (ch);
}




void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin==GPIO_PIN_13)
        HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_12); 
	
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
 
  
 static unsigned char ledState = 0;  
if (htim==(&htim2))
{
  if (ledState == 0)
            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_RESET);
        else
            HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,GPIO_PIN_SET);
        ledState = !ledState;
}


}