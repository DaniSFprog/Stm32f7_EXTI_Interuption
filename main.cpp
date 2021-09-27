#include <stdio.h>
#include <stm32f746xx.h>
		int BCD [16] = {0X01,0X4F,0x12,0x06,0x4C,0X24,0X20,0X0F,0X00,0X04,0x08,0X60,0X31,0X42,0X30,0x38};	
		int numero = 0;

extern "C"{
		void EXTI0_IRQHandler(void){	
		EXTI->PR |=0x0001; 		
		numero++;
		if(numero==16){
		numero=0;
	  if(numero<0){
		numero=15;}
		}		
	}
}

int main(void){
	RCC->APB2ENR |= 0X00004000;		//ACTIVATE SYSTEM CONFIGURATION CONTROLLER CLOCK ENABLE
	RCC->AHB1ENR |= 0x00000022;  // ACTIVATE CLOCK GPIOD, GPIOB, GPIOC, GPIOF AND GPIOG
	//CONFIGURACION PINES B
	GPIOB->MODER =  0x00001555;        //Pines del PB0 al PB7 como salida  7 segmentos
	GPIOB->OTYPER = 0;
	GPIOB->OSPEEDR = 0x00001555;       //medium speed
	GPIOB->PUPDR =  0x00001555;        //pull up
	//CONFIGURACION PINES F	
	GPIOF->MODER |=  0x00000000;
	GPIOF->PUPDR |=  0x00000002;	
	SYSCFG->EXTICR[0] |= 0X0005;	//ACTIVA EXTI0 EN PF0
	EXTI->IMR |= 0X00000001;		//ACTIVATE INTERRUPT 1
	EXTI->FTSR |= 0X00000001; //flanco de bajada
	NVIC_EnableIRQ(EXTI0_IRQn);	// ENABLE VECTOR INTERRUPT EXTI0 
	while(true){	
	GPIOB->ODR = BCD[numero]; 
	}//END WHILE
}//END MAIN