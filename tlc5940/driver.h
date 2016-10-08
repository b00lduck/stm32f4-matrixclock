#pragma once
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"

#define SIG_GSCLK_PORT			GPIOA
#define SIG_GSCLK_PORT_CLK    	RCC_AHB1Periph_GPIOA
#define SIG_GSCLK_PIN			GPIO_Pin8
#define SIG_GSCLK_PINSOURCE		GPIO_PinSource8
#define SIG_GSCLK_PIN_AF		GPIO_AF_TIM1

#define SIG_GSCLK_TIMER			TIM1
#define SIG_GSCLK_TIMER_CLK		RCC_APB2Periph_TIM1


// AF2 of PORTC -> TIM3
#define SIG_BLANK_PORT			GPIOC
#define SIG_BLANK_PORT_CLK    	RCC_AHB1Periph_GPIOC
#define SIG_BLANK_PIN			GPIO_Pin_6
#define SIG_BLANK_PINSOURCE		GPIO_PinSource6
#define SIG_BLANK_PIN_AF		GPIO_AF_TIM3

// AF2 of PORTC -> TIM3
#define SIG_LATCH_PORT			GPIOC
#define SIG_LATCH_PORT_CLK    	RCC_AHB1Periph_GPIOC
#define SIG_LATCH_PIN			GPIO_Pin_7
#define SIG_LATCH_PINSOURCE		GPIO_PinSource7
#define SIG_LATCH_PIN_AF		GPIO_AF_TIM3

#define SIG_MAIN_TIMER			TIM3
#define SIG_MAIN_TIMER_CLK		RCC_APB1Periph_TIM3
#define SIG_MAIN_TIMER_CC_IRQ 	TIM3_IRQn


#define SIG_DATA_PORT_CLK		RCC_AHB1Periph_GPIOD
#define SIG_DATA_PORT			GPIOD
#define SIG_DATA_SDA_PIN		GPIO_Pin_10
#define SIG_DATA_SCK_PIN		GPIO_Pin_11

void tlc5940_init(void);

void tim1_init(void);
void tim3_init(void);
void data_init(void);

extern uint8_t goForIt;

