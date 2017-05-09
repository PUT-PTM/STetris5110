#include<stm32f4xx_exti.h>
#include<stm32f4xx_gpio.h>
#include<stm32f4xx_rcc.h>
#include<stm32f4xx_tim.h>
#include<stm32f4xx_syscfg.h>
#include "tm_stm32f4_gpio.h"
#include "tm_stm32f4_pcd8544.h"
#include "tm_stm32f4_spi.h"
#include "misc.h"
#define WIDTH 30
#define LENGTH 60

int punkty=0;

typedef struct
{
int jest;
int utw;
int spawned;
}bloczek;

void utwspawned(bloczek** tab)
{
	int j=0;
for(j;j<LENGTH;j++) for(int i=0;i<WIDTH;i++) if(tab[i][j].spawned)tab[i][j].utw=1;
j=0;
for(j;j<LENGTH;j++) for(int i=0;i<WIDTH;i++)tab[i][j].spawned=0;
}

void spawn(bloczek** tab){
	tab[WIDTH/2][0].jest=1;
	tab[WIDTH/2][1].jest=1;
	tab[WIDTH/2-1][1].jest=1;
	tab[WIDTH/2+1][0].jest=1;
	tab[WIDTH/2][0].spawned=1;
	tab[WIDTH/2][1].spawned=1;
	tab[WIDTH/2-1][1].spawned=1;
	tab[WIDTH/2+1][0].spawned=1;
}

void wszystkowdol(int n, bloczek** tab)
{
for(int k=0;k<WIDTH;k++)
    {
        tab[k][n].jest=0;
        tab[k][n].utw=0;
        tab[k][n].spawned=0;
        punkty+=WIDTH*4;
    }
for(int i=n-1;i>0;i--)for(int j=0;j<WIDTH;j++){
        tab[j][i].jest=tab[j][i-1].jest;
        tab[j][i].utw=tab[j][i-1].utw;
        tab[j][i].spawned=tab[j][i-1].spawned;
    }
}
void zakonczgre()
{

}

void print(bloczek** tab)
{
	 for(int j=0;j<LENGTH;j++)
	 {
		 for(int i=0;i<WIDTH;i++)
	 	 {
		 if(tab[i][j].jest==1)PCD8544_DrawPixel(i, j, PCD8544_Pixel_Set);
	     }
	 }
}

void TIM3_IRQHandler(bloczek** tab)//TIMER odpowiedzialny za "ticki" gry i "spadanie" klock�w. f= 1Hz
{
             if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
             {

            	 for(int j=LENGTH-1;j>-1;j--){
            	         for(int i=0;i<WIDTH;i++)
            	         {
            	             if(tab[i][j].utw==1)continue;//Z jakiegos powodu po zmianie bool na int gdzies jest blad, dopisanie == 1 pomoglo...
            	             if(j==LENGTH-1 && tab[i][j].jest==1)
            	                 {
            	                 //Jesli bloczek jest na samym dole, utwierdzamy (nie spada)
            	                 utwspawned(tab);
            	                 }
            	             else if(tab[i][j+1].utw==1 && tab[i][j].jest==1 &&tab[i][j].utw==0)
            	                 {
            	                 //Jesli bloczek jest na polu i,j, a pod nim jest bloczek utwierdzony, utwierdzamy tez bloczek na pol i,j
            	                 utwspawned(tab);
            	                 }

            	         }
            	          for(int i=0;i<WIDTH;i++)if(tab[i][j].jest==1 && tab[i][j+1].jest==0 && tab[i][j].utw==0)//Jesli bloczek jest na polu i,j i nic pod nim nic nie ma, spada nizej o 1
            	                 {
            	                 tab[i][j].jest=0;
            	                 tab[i][j+1].jest=1;
            	                 tab[i][j+1].utw=0;
            	                 tab[i][j+1].spawned=tab[i][j].spawned;
            	                 tab[i][j].spawned=0;
            	                 }
            	 }
            	 for(int j=0;j<LENGTH;j++)
            	     {
            	         int suma=0;
            	         for(int i=0;i<WIDTH;i++){
            	         suma+=tab[i][j].jest;
            	         }
            	         if(suma==WIDTH)wszystkowdol(j,tab);
            	 }
            	 for(int i=0;i<WIDTH;i++)if(tab[i][0].utw==1)zakonczgre();
            	 //->Clear screen na wyswietlaczu
            	 TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
             }
}
void TIM2_IRQHandler(bloczek** tab)//Odpowiedzialny za wyswietlanie i update wyswietlacza (f= 100 Hz)
{
             if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
             {
            	    print(tab);//->Print na wyswietlaczu
                    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
             }
}

int main(void)
{
	SystemInit();
	/*
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);


	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructure.TIM_Period = 839;
	TIM_TimeBaseStructure.TIM_Prescaler = 999;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode =  TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure2;
	TIM_TimeBaseStructure2.TIM_Period = 8399;
	TIM_TimeBaseStructure2.TIM_Prescaler = 9999;
	TIM_TimeBaseStructure2.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure2.TIM_CounterMode =  TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure2);

	TIM_Cmd(TIM2, ENABLE);
	TIM_Cmd(TIM3, ENABLE);

	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitTypeDef NVIC_InitStructure2;
	NVIC_InitStructure2.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure2.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure2.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure2.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure2);

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	NVIC_InitTypeDef NVIC_InitStructure3;
	NVIC_InitStructure3.NVIC_IRQChannel = EXTI1_IRQn;
	NVIC_InitStructure3.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure3.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStructure3.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure3);

	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	EXTI_InitTypeDef EXTI_InitStructure2;
	EXTI_InitStructure2.EXTI_Line = EXTI_Line2;
	EXTI_InitStructure2.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure2.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure2.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure2);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource2);
*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitTypeDef LED_Config;
		LED_Config.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
		LED_Config.GPIO_Mode = GPIO_Mode_OUT;
		LED_Config.GPIO_OType = GPIO_OType_PP;
		LED_Config.GPIO_Speed = GPIO_Speed_25MHz;
		LED_Config.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &LED_Config);


	 	PCD8544_Init(0x38);
	    PCD8544_Init(0x38);

	     //Go to x=14, y=3 position
	     PCD8544_GotoXY(14, 3);

	     //Print data with Pixel Set mode and Fontsize of 5x7px
	     PCD8544_Puts("STM32F429", PCD8544_Pixel_Clear, PCD8544_FontSize_5x7);
	     PCD8544_GotoXY(15, 13);
	     PCD8544_Puts("Discovery", PCD8544_Pixel_Set, PCD8544_FontSize_5x7);
	     PCD8544_GotoXY(30, 26);
	     PCD8544_Puts("2014", PCD8544_Pixel_Clear, PCD8544_FontSize_5x7);

	     PCD8544_GotoXY(45, 42);
	     //Put string with Pixel set mode and Fontsize of 3x5
	     PCD8544_Puts("majerle.eu", PCD8544_Pixel_Set, PCD8544_FontSize_3x5);

	     //Display data on LCD
	     PCD8544_Refresh();
	    GPIO_SetBits(GPIOD,GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);







}
