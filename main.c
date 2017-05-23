#include<stm32f4xx_exti.h>
#include<stm32f4xx_gpio.h>
#include<stm32f4xx_rcc.h>
#include<stm32f4xx_tim.h>
#include<stm32f4xx_syscfg.h>
#include "tm_stm32f4_gpio.h"
#include "tm_stm32f4_pcd8544.h"
#include "tm_stm32f4_spi.h"
#include "misc.h"
#define WIDTH 20
#define LENGTH 20

int punkty=0;
void Configure_PD0(void) {
    /* Set variables used */
    GPIO_InitTypeDef GPIO_InitStruct;
    EXTI_InitTypeDef EXTI_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;

    /* Enable clock for GPIOD */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    /* Enable clock for SYSCFG */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

    /* Set pin as input */
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOD, &GPIO_InitStruct);

    /* Tell system that you will use PD0 for EXTI_Line0 */
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource0);

    /* PD0 is connected to EXTI_Line0 */
    EXTI_InitStruct.EXTI_Line = EXTI_Line0;
    /* Enable interrupt */
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    /* Interrupt mode */
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    /* Triggers on rising and falling edge */
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    /* Add to EXTI */
    EXTI_Init(&EXTI_InitStruct);

    /* Add IRQ vector to NVIC */
    /* PD0 is connected to EXTI_Line0, which has EXTI0_IRQn vector */
    NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
    /* Set priority */
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
    /* Set sub priority */
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
    /* Enable interrupt */
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    /* Add to NVIC */
    NVIC_Init(&NVIC_InitStruct);
}

void Configure_PB12(void) {
    /* Set variables used */
    GPIO_InitTypeDef GPIO_InitStruct;
    EXTI_InitTypeDef EXTI_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;

    /* Enable clock for GPIOB */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    /* Enable clock for SYSCFG */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

    /* Set pin as input */
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* Tell system that you will use PB12 for EXTI_Line12 */
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource12);

    /* PB12 is connected to EXTI_Line12 */
    EXTI_InitStruct.EXTI_Line = EXTI_Line12;
    /* Enable interrupt */
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    /* Interrupt mode */
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    /* Triggers on rising and falling edge */
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    /* Add to EXTI */
    EXTI_Init(&EXTI_InitStruct);

    /* Add IRQ vector to NVIC */
    /* PB12 is connected to EXTI_Line12, which has EXTI15_10_IRQn vector */
    NVIC_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn;
    /* Set priority */
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
    /* Set sub priority */
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x01;
    /* Enable interrupt */
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    /* Add to NVIC */
    NVIC_Init(&NVIC_InitStruct);
}

/* Set interrupt handlers */
/* Handle PD0 interrupt */
typedef struct
{
int jest;
int utw;
int spawned;
}bloczek;
bloczek tab[WIDTH][LENGTH];


void spawn(){
	tab[WIDTH/2][0].jest=1;
	tab[WIDTH/2][1].jest=1;
	tab[WIDTH/2-1][1].jest=1;
	tab[WIDTH/2+1][0].jest=1;
	tab[WIDTH/2][0].spawned=1;
	tab[WIDTH/2][1].spawned=1;
	tab[WIDTH/2-1][1].spawned=1;
	tab[WIDTH/2+1][0].spawned=1;

}
void utwspawned()
{
int i,j;
for(j=0;j<LENGTH;j++) for(i=0;i<WIDTH;i++)if(tab[i][j].spawned)tab[i][j].utw=1;
for(j=0;j<LENGTH;j++) for(i=0;i<WIDTH;i++)tab[i][j].spawned=0;
spawn();
}
void wszystkowdol(int n)
{
	int i,j,k;
for(k=0;k<WIDTH;k++)
    {
        tab[k][n].jest=0;
        tab[k][n].utw=0;
        tab[k][n].spawned=0;
        punkty+=WIDTH*4;
    }
for(i=n-1;i>0;i--)for(j=0;j<WIDTH;j++){
        tab[j][i].jest=tab[j][i-1].jest;
        tab[j][i].utw=tab[j][i-1].utw;
        tab[j][i].spawned=tab[j][i-1].spawned;
    }
}
void zakonczgre()
{


   PCD8544_GotoXY(24, 48);

   //Print data with Pixel Set mode and Fontsize of 5x7px
   PCD8544_Puts("KONIEC GRY", PCD8544_Pixel_Set, PCD8544_FontSize_5x7);

   PCD8544_Refresh();
}



void TIM3_IRQHandler()//TIMER odpowiedzialny za "ticki" gry i "spadanie" klocków. f= 1Hz
{


             if(TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
             {
            	 int i,j;
            	 GPIO_ToggleBits(GPIOD,GPIO_Pin_13);
            	 for(j=LENGTH-1;j>-1;j--){
            	         for(i=0;i<WIDTH;i++)
            	         {
            	             if(tab[i][j].utw==1)continue;
            	             if(j==LENGTH-1 && tab[i][j].jest==1)
            	                 {

            	                 utwspawned(tab);

            	                 }
            	             else if(tab[i][j+1].utw==1 && tab[i][j].jest==1 &&tab[i][j].utw==0)
            	                 {

            	                 utwspawned(tab);

            	                 }

            	         }
            	          for(i=0;i<WIDTH;i++)if(tab[i][j].jest==1 && tab[i][j+1].jest==0 && tab[i][j].utw==0)//Jesli bloczek jest na polu i,j i nic pod nim nic nie ma, spada nizej o 1
            	                 {
            	                 tab[i][j].jest=0;
            	                 tab[i][j+1].jest=1;
            	                 tab[i][j+1].utw=0;
            	                 tab[i][j+1].spawned=tab[i][j].spawned;
            	                 tab[i][j].spawned=0;
            	                 }
            	 }
            	 int suma=0;
            	 for(j=0;j<LENGTH;j++)
            	     {

            	         for(i=0;i<WIDTH;i++){
            	         suma+=tab[i][j].jest;
            	         }
            	         if(suma==WIDTH)wszystkowdol(j);
            	         suma=0;
            	 }
            	 for(i=0;i<WIDTH;i++)if(tab[i][0].utw==1)zakonczgre();
            	 PCD8544_Clear();
            	 TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
             }
}
void TIM2_IRQHandler()//Odpowiedzialny za wyswietlanie i update wyswietlacza (f= 100 Hz)
{
             if(TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
             {

            	 int i,j;
            	 	 for(j=0;j<LENGTH;j++)
            	 	 {
            	 		 for(i=0;i<WIDTH;i++)
            	 	 	 {
            	 		 PCD8544_GotoXY(i,j);
            	 		 if(tab[i][j].jest==1){
            	 			PCD8544_DrawPixel(i, j, PCD8544_Pixel_Set);
            	 			PCD8544_Refresh();

            	 		 }else{
            	 			PCD8544_DrawPixel(i, j, PCD8544_Pixel_Clear);
            	 			PCD8544_Refresh();

            	 		 }
            	 	     }
            	 	 }

                    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
             }
}
void EXTI0_IRQHandler(void) {
    /* Make sure that interrupt flag is set */
    if (EXTI_GetITStatus(EXTI_Line0) != RESET) {
    	int i,j;
    	int flag=1;
    	for(i=0;i<0x3FFFFF;i++){}
    	GPIO_ToggleBits(GPIOD,GPIO_Pin_15);
    					 for(j=0;j<LENGTH;j++)
    	           	 	 {
    	           	 		for(i=0;i<WIDTH;i++)
    	           	 	 	{
    	           	 		if(tab[i][j].spawned==1){
    	           	 		if(tab[i-1][j].utw==1||(i-1)==-1){
    	           	 		flag=0;
    	           	 		}
    	           	 		}

    	           	 	 	 }
    	           	 	 }
    					for(j=0;j<LENGTH;j++)
    					{
    					  for(i=0;i<WIDTH;i++)
    					  {
    						  if(flag&&tab[i][j].spawned==1)
    						  {
    							  if(tab[i][j].utw==0&&tab[i][j].spawned==1){
    							  tab[i-1][j].jest=tab[i][j].jest;
    						      tab[i-1][j].spawned=tab[i][j].spawned;
    						      tab[i-1][j].utw=tab[i][j].utw;
    						      tab[i][j].spawned=0;
    						      tab[i][j].utw=0;
    						      tab[i][j].jest=0;
    							  }
    					  	  }
    					   }
    					}

        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}


void EXTI15_10_IRQHandler(void) {

    if (EXTI_GetITStatus(EXTI_Line12) != RESET) {
    	int i,j;
    	int flag=1;
    	for(j=0;j<LENGTH;j++)
    	           	 	 {
    	           	 		 for(i=0;i<WIDTH;i++)
    	           	 	 	{
    	           	 		if(tab[i][j].spawned==1){
    	           	 		if(tab[i+1][j].utw==1||(i+1)==WIDTH){
    	           	 		flag=0;
    	           	 		}
    	           	 		}

    	           	 	 	 }
    	           	 	 }
    					for(j=LENGTH-1;j>-1;j--)
    					{
    					  for(i=WIDTH-1;i>-1;i--)
    					  {
    						  if(flag&&tab[i][j].spawned==1)
    						     						  {
    						     							  if(tab[i][j].utw==0&&tab[i][j].spawned==1){
    						     							  tab[i+1][j].jest=tab[i][j].jest;
    						     						      tab[i+1][j].spawned=tab[i][j].spawned;
    						     						      tab[i+1][j].utw=tab[i][j].utw;
    						     						      tab[i][j].spawned=0;
    						     						      tab[i][j].utw=0;
    						     						      tab[i][j].jest=0;
    						     							  }
    						     					  	  }
    					  	  }
    					   }



        EXTI_ClearITPendingBit(EXTI_Line12);
    }
}
int main(void)
{
	SystemInit();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);


    int i,j;
	for(j=0;j<LENGTH;j++)
	{
	  for(i=0;i<15;i++)
	  {
	  tab[i][j].jest=0;
	  tab[i][j].spawned=0;
	  tab[i][j].utw=0;
	  }
	}

	spawn();


		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
		TIM_TimeBaseStructure.TIM_Period = 209;
		TIM_TimeBaseStructure.TIM_Prescaler = 249;
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseStructure.TIM_CounterMode =  TIM_CounterMode_Up;
		TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);


		TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure2;
		TIM_TimeBaseStructure2.TIM_Period = 8399;
		TIM_TimeBaseStructure2.TIM_Prescaler = 4999;
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
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
			TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

			NVIC_InitTypeDef NVIC_InitStructure2;
			NVIC_InitStructure2.NVIC_IRQChannel = TIM3_IRQn;
			NVIC_InitStructure2.NVIC_IRQChannelPreemptionPriority = 0x00;
			NVIC_InitStructure2.NVIC_IRQChannelSubPriority = 0x00;
			NVIC_InitStructure2.NVIC_IRQChannelCmd = ENABLE;
			NVIC_Init(&NVIC_InitStructure2);
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
			TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

			Configure_PD0();
			Configure_PB12();






		GPIO_InitTypeDef LED_Config;
		LED_Config.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13| GPIO_Pin_14| GPIO_Pin_15;
		LED_Config.GPIO_Mode = GPIO_Mode_OUT;
		LED_Config.GPIO_OType = GPIO_OType_PP;
		LED_Config.GPIO_Speed = GPIO_Speed_25MHz;
		LED_Config.GPIO_PuPd = GPIO_PuPd_NOPULL;
	    GPIO_Init(GPIOD, &LED_Config);


	 	PCD8544_Init(0x38);

	 	while(1){
	 /*	if(TIM_GetFlagStatus(TIM2, TIM_FLAG_Update)) {

	 		  TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	 		}
	 		if(TIM_GetFlagStatus(TIM3, TIM_FLAG_Update)) {

	 			TIM_ClearFlag(TIM3, TIM_FLAG_Update);
	 			 		}
*/
	 	}












}
