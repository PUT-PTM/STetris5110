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
#define LENGTH 20
void Configure_PD0(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    EXTI_InitTypeDef EXTI_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOD, &GPIO_InitStruct);
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource0);
    EXTI_InitStruct.EXTI_Line = EXTI_Line0;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    EXTI_Init(&EXTI_InitStruct);
    NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
}
void Configure_PB12(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    EXTI_InitTypeDef EXTI_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOB, &GPIO_InitStruct);
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource12);
    EXTI_InitStruct.EXTI_Line = EXTI_Line12;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    EXTI_Init(&EXTI_InitStruct);
    NVIC_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x01;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
}
void Configure_PA5(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;
    EXTI_InitTypeDef EXTI_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource5);
    EXTI_InitStruct.EXTI_Line = EXTI_Line5;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    EXTI_Init(&EXTI_InitStruct);
    NVIC_InitStruct.NVIC_IRQChannel = EXTI9_5_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStruct);
}
typedef struct
{
int jest;
int utw;
int spawned;
}bloczek;
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bloczek tab[WIDTH][LENGTH];
int punkty=0;
int height;
int br=WIDTH/2;
int it=2;
int current;
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void rotacja(){
int i,j;
if(current==1)return;
for(j=LENGTH-1;j>=0;j--)for(i=0;i<WIDTH;i++){
	if(tab[i][j].spawned==1){
		height=j;
		br=i;
		break;

	}
	}

for(j=0;j<LENGTH;j++)for(i=0;i<WIDTH;i++)if(tab[i][j].spawned)
	{
		tab[i][j].jest=0;
		tab[i][j].spawned=0;
	}
if(current==0&&tab[br][height].jest==0 && tab[br][height+1].jest==0 && tab[br+1][height+1].jest==0 && tab[br+1][height+2].jest==0){


    tab[br][height].jest=1;
	tab[br][height+1].jest=1;
	tab[br+1][height+1].jest=1;
	tab[br+1][height+2].jest=1;
	tab[br][height].spawned=1;
	tab[br][height+1].spawned=1;
	tab[br+1][height+1].spawned=1;
	tab[br+1][height+2].spawned=1;
	current=2;
	//Obni¿amy wysokoœæ poniewa¿ po rotacji figura druga ma "nizej" srodek ciê¿koœci
	return;
	}
if(current==2&&tab[br][height].jest==0&&tab[br][height+1].jest==0&&tab[br-1][height+1].jest==0&&tab[br+1][height].jest==0){

	tab[br][height].jest=1;
	tab[br][height+1].jest=1;
	tab[br-1][height+1].jest=1;
	tab[br+1][height].jest=1;
	tab[br][height].spawned=1;
	tab[br][height+1].spawned=1;
	tab[br-1][height+1].spawned=1;
	tab[br+1][height].spawned=1;
	current=0;
	return;
}
if(current==3&&tab[br][height].jest==0&&tab[br][height+1].jest==0&&tab[br][height+2].jest==0&&tab[br][height+3].jest==0)
{



	tab[br][height].jest=1;
	tab[br][height+1].jest=1;
	tab[br][height+2].jest=1;
	tab[br][height+3].jest=1;

	tab[br][height].spawned=1;
	tab[br][height+1].spawned=1;
	tab[br][height+2].spawned=1;
	tab[br][height+3].spawned=1;

	current=4;

	return;
}
if(current==4&&tab[br][height].jest==0&&tab[br-1][height].jest==0&&tab[br+1][height].jest==0&&tab[br+2][height].jest==0)
{

    tab[br][height].jest=1;
	tab[br+2][height].jest=1;
	tab[br-1][height].jest=1;
	tab[br+1][height].jest=1;
	tab[br][height].spawned=1;
	tab[br+2][height].spawned=1;
	tab[br-1][height].spawned=1;
	tab[br+1][height].spawned=1;
	current=3;
	return;
}
if(current==1)return;
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void spawn(){
	int j,i;
	for(j=0;j<LENGTH;j++)for(i=0;i<WIDTH;i++)if(tab[i][j].spawned)return;
    br=WIDTH/2;
    current=it%5;
	switch(it%5){
	case 0:{
	/*

	  o-
     --

     0->2

	*/
	tab[WIDTH/2][0].jest=1;
	tab[WIDTH/2][1].jest=1;
	tab[WIDTH/2-1][1].jest=1;
	tab[WIDTH/2+1][0].jest=1;
	tab[WIDTH/2][0].spawned=1;
	tab[WIDTH/2][1].spawned=1;
	tab[WIDTH/2-1][1].spawned=1;
	tab[WIDTH/2+1][0].spawned=1;

	break;
	}
	case 1:{
	/*

	o-
    --

	*/

	tab[WIDTH/2][0].jest=1;
	tab[WIDTH/2][1].jest=1;
	tab[WIDTH/2+1][0].jest=1;
	tab[WIDTH/2+1][1].jest=1;
	tab[WIDTH/2][0].spawned=1;
	tab[WIDTH/2][1].spawned=1;
	tab[WIDTH/2+1][0].spawned=1;
	tab[WIDTH/2+1][1].spawned=1;

	break;
	}

	case 2:{
	/*
	  -
      o-
       -
	*/
	tab[WIDTH/2][0].jest=1;
	tab[WIDTH/2][1].jest=1;
	tab[WIDTH/2+1][0+1].jest=1;
	tab[WIDTH/2+1][0+2].jest=1;
	tab[WIDTH/2][0].spawned=1;
	tab[WIDTH/2][0+1].spawned=1;
	tab[WIDTH/2+1][0+1].spawned=1;
	tab[WIDTH/2+1][0+2].spawned=1;

	break;
	}
	case 3:{
	/*

	-o--

    3->4

	*/
	tab[WIDTH/2][0].jest=1;
	tab[WIDTH/2+2][0].jest=1;
	tab[WIDTH/2-1][0].jest=1;
	tab[WIDTH/2+1][0].jest=1;
	tab[WIDTH/2][0].spawned=1;
	tab[WIDTH/2+2][0].spawned=1;
	tab[WIDTH/2-1][0].spawned=1;
	tab[WIDTH/2+1][0].spawned=1;

	break;
	}
	case 4:{
	/*

	-
	-
	o
	-

	height ustawiany na 2 poniewa¿ "oœ obrotu" znajduje siê w miejscu kropki. Jest ponizej srodka by uniknac "wspinania siê" przez ci¹g³e rotacje
	*/
	tab[WIDTH/2][0].jest=1;
	tab[WIDTH/2][0+1].jest=1;
	tab[WIDTH/2][0+2].jest=1;
	tab[WIDTH/2][0+3].jest=1;
	tab[WIDTH/2][0].spawned=1;
	tab[WIDTH/2][0+1].spawned=1;
	tab[WIDTH/2][0+2].spawned=1;
	tab[WIDTH/2][0+3].spawned=1;

	break;
	}



	}
	it+=4;

}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void wszystkowdol(int n)
{
int k;
for(k=0;k<WIDTH;k++)
    {
        tab[k][n].jest=0;
        tab[k][n].utw=0;
        tab[k][n].spawned=0;
        punkty+=WIDTH*4;

        int i,j;
        for(i=0;i<WIDTH;i++){
        for(j=n;j>0;j--){
        tab[i][j].spawned = tab[i][j-1].spawned;
        tab[i][j].utw = tab[i][j-1].utw ;
        tab[i][j].jest = tab[i][j-1].jest ;
        }
        }
        for(i=0;i<WIDTH;i++){
        tab[i][0].spawned = 0;
        tab[i][0].utw = 0;
        tab[i][0].jest = 0;
        }
      }
    }
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void utwspawned()
{
	int i,j;
	for(j=0;j<LENGTH;j++)for(i=0;i<WIDTH;i++)if(tab[i][j].spawned)
	{
	tab[i][j].utw=1;

	}
	for(j=0;j<LENGTH;j++)for(i=0;i<WIDTH;i++)tab[i][j].spawned=0;
	spawn();
}
//-
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

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


            	 for(j=0;j<LENGTH;j++)
            	            	     {
            	            	         int suma=0;
            	            	         int i;
            	            	         for(i=0;i<WIDTH;i++){
            	            	         suma+=tab[i][j].jest;
            	            	         }
            	            	         if(suma==WIDTH)wszystkowdol(j);
            	            	     }
            	 for(j=0;j<LENGTH;j++)if(tab[j][0].utw==1){
            		 int punkt=punkty;
            		 	 while(1){


            		             	 	PCD8544_GotoXY(35,10);
            		             	    PCD8544_Putc(((punkt/1000)+0x30), PCD8544_Pixel_Set, PCD8544_FontSize_5x7);
            		             	                	    punkt=punkt-(punkt/1000)*1000;
            		             	    PCD8544_GotoXY(41, 10);
            		             	    PCD8544_Putc(((punkt%100)+0x30), PCD8544_Pixel_Set, PCD8544_FontSize_5x7);

            		             	    punkt=punkt-(punkt/100)*100;
            		             	    PCD8544_GotoXY(47, 10);
            		             	    PCD8544_Putc(((punkt%10)+0x30), PCD8544_Pixel_Set, PCD8544_FontSize_5x7);

            		             	    punkt=punkt-(punkt/10)*10;
            		             	    PCD8544_GotoXY(53, 10);
            		             	    PCD8544_Putc(((punkt)+0x30), PCD8544_Pixel_Set, PCD8544_FontSize_5x7);
            		             	    punkt=punkty;
            		             	    PCD8544_Refresh();


            		 	}
            	 }

            	 PCD8544_Clear();
            	 TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
             }
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
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
							if(tab[i][j].jest==1)
							{
            	 			PCD8544_DrawPixel(i, j, PCD8544_Pixel_Set);
            	 			PCD8544_Refresh();
							}else
							{
            	 			PCD8544_DrawPixel(i, j, PCD8544_Pixel_Clear);
            	 			PCD8544_Refresh();
							}
            	 	    }
            	 	}


            	 	PCD8544_Refresh();
                    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
             }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void EXTI0_IRQHandler(void) {
    if (EXTI_GetITStatus(EXTI_Line0) != RESET)
	{
    	int i,j;
    	int flag=1;
    	for(i=0;i<0x3FFFFF;i++){}

    					 for(j=0;j<LENGTH;j++)
    	           	 	 {
    	           	 		for(i=0;i<WIDTH;i++)
    	           	 	 	{
								if(tab[i][j].spawned==1)
								{
									if(tab[i-1][j].utw==1||(i-1)==-1)
									{
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
    							if(tab[i][j].utw==0&&tab[i][j].spawned==1)
								{
    							tab[i-1][j].jest=tab[i][j].jest;
    						    tab[i-1][j].spawned=tab[i][j].spawned;
    						    tab[i-1][j].utw=tab[i][j].utw;
    						    tab[i][j].spawned=0;
    						    tab[i][j].utw=0;
    						    tab[i][j].jest=0;
    						    br--;
    							}
    					  	  }
    					   }
    					}

        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void EXTI9_5_IRQHandler(void) {
	int i;
	for(i=0;i<0x2FFFFF;i++){}
	rotacja();
	EXTI_ClearITPendingBit(EXTI_Line5);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void EXTI15_10_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line12) != RESET)
	{
    	int i,j;
    	int flag=1;
    	for(j=0;j<LENGTH;j++)
    	{
			for(i=0;i<WIDTH;i++)
    	    {
				if(tab[i][j].spawned==1)
				{
					if(tab[i+1][j].utw==1||(i+1)==WIDTH)
					{
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
					if(tab[i][j].utw==0&&tab[i][j].spawned==1)
					{
    				tab[i+1][j].jest=tab[i][j].jest;
    				tab[i+1][j].spawned=tab[i][j].spawned;
    				tab[i+1][j].utw=tab[i][j].utw;
    				tab[i][j].spawned=0;
    				tab[i][j].utw=0;
    				tab[i][j].jest=0;
    				br++;
    				}
    			}
    		}
    	}
	EXTI_ClearITPendingBit(EXTI_Line12);
    }
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
int main(void)
{
	SystemInit();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

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
	Configure_PA5();

	int i,j;
	for(j=0;j<LENGTH;j++)
	{
	  for(i=0;i<WIDTH;i++)
	  {
	  tab[i][j].jest=0;
	  tab[i][j].spawned=0;
	  tab[i][j].utw=0;
	  }
	}

	spawn();

	PCD8544_Init(0x38);

	while(1){}












}
