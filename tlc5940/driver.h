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
#define SIG_BLANK_TIMER_CC_IRQ  TIM1_CC_IRQn

//#define TLCPWM_TIMER_CC2		50 // start of line interrupt


#define SIG_GSCLK_PORT				GPIOC
#define SIG_GSCLK_PORT_CLK    		RCC_AHB1Periph_GPIOC
#define SIG_GSCLK_PIN				GPIO_Pin_6
#define SIG_GSCLK_PINSOURCE			GPIO_PinSource6
#define SIG_GSCLK_PIN_AF			GPIO_AF_TIM3

#define SIG_GSCLK_TIMER				TIM3
#define SIG_GSCLK_TIMER_CLK			RCC_APB1Periph_TIM3
#define SIG_GSCLK_TIMER_CC_IRQ  	TIM3_IRQn

//#define SIG_GSCLK_TIMER_CC2 		1

void tlc5940_init(void);
