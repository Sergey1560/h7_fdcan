#include "main.h"

int main(void){

	//MPU_Config();	

	INFO("System start");
	#ifdef ENABLE_DCACHE
	SCB_EnableICache();
	SCB_EnableDCache();
	#endif

	RCC_init();
	can1_init();
	timer2_init();
	
	while(1){
	};
}

void timer2_init(void){
	RCC->APB1LENR |= RCC_APB1LENR_TIM2EN;
	__DSB();
	TIM2->PSC = (uint16_t)(TIM2_CLK/1000000)-1;
	TIM2->ARR = 1000000 - 1; 	
	TIM2->DIER |= TIM_DIER_UIE;
	__DSB();
	TIM2->CR1 |= TIM_CR1_CEN;
	
	NVIC_EnableIRQ(TIM2_IRQn);
	NVIC_SetPriority (TIM2_IRQn, 5);
}

void ITCM TIM2_IRQHandler(void)
{
	if(TIM2->SR & TIM_SR_UIF)	TIM2->SR &= ~TIM_SR_UIF; 

	if(TIM2->PSC == 0){
		ERROR("TIM PSC = 0");
		while(1){};
	}
	can_send_next();


}

