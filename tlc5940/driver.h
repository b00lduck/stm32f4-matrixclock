#pragma once
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"

#define SIG_BLANK_PORT			GPIOA
#define SIG_BLANK_PORT_CLK    	RCC_AHB1Periph_GPIOA
#define SIG_BLANK_PIN			GPIO_Pin8
#define SIG_BLANK_PINSOURCE		GPIO_PinSource8
#define SIG_BLANK_PIN_AF		GPIO_AF_TIM1

#define SIG_BLANK_TIMER			TIM1
#define SIG_BLANK_TIMER_CLK		RCC_APB2Periph_TIM1


#define SIG_GSCLK_PORT			GPIOC
#define SIG_GSCLK_PORT_CLK    	RCC_AHB1Periph_GPIOC
#define SIG_GSCLK_PIN			GPIO_Pin_6
#define SIG_GSCLK_PINSOURCE		GPIO_PinSource6
#define SIG_GSCLK_PIN_AF		GPIO_AF_TIM3

#define SIG_GSCLK_TIMER			TIM3
#define SIG_GSCLK_TIMER_CLK		RCC_APB1Periph_TIM3


void tlc5940_init(void);

void tim1_init();
void tim3_init();


	// Be a slave of SIG_BLANK_TIMER
// TIM_SelectMasterSlaveMode(SIG_GSCLK_TIMER, TIM_SlaveMode_Gated);
// TIM_SelectInputTrigger(SIG_GSCLK_TIMER, TIM_TS_ITR0);



/*
 * 	// PWM1 Mode configuration: Channel2
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputNState_Disable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	TIM_OCInitStructure.TIM_Pulse = 55;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OC2Init(SIG_BLANK_TIMER, &TIM_OCInitStructure);

	// enable the counter
	TIM_Cmd(SIG_BLANK_TIMER, ENABLE);

	// Main Output Enable
	TIM_CtrlPWMOutputs(SIG_BLANK_TIMER, ENABLE);

	// Enable Master/Slave mode
//  	TIM_SelectMasterSlaveMode(SIG_BLANK_TIMER, TIM_MasterSlaveMode_Enable);

//  	TIM_SelectOutputTrigger(SIG_BLANK_TIMER, TIM_TRGOSource_OC2Ref);
 */
