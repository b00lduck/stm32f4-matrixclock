#pragma once


// Main timer
#define SIG_MAIN_TIMER				TIM3
#define SIG_MAIN_TIMER_CLK			RCC_APB1Periph_TIM3
#define SIG_MAIN_TIMER_CC_IRQ 		TIM3_IRQn

// AF2 of PORTC -> TIM3
#define SIG_BLANK_PORT				GPIOC
#define SIG_BLANK_PORT_CLK    		RCC_AHB1Periph_GPIOC
#define SIG_BLANK_PIN				GPIO_Pin_6
#define SIG_BLANK_PINSOURCE			GPIO_PinSource6
#define SIG_BLANK_PIN_AF			GPIO_AF_TIM3

// AF2 of PORTC -> TIM3
#define SIG_LATCH_PORT				GPIOC
#define SIG_LATCH_PORT_CLK    		RCC_AHB1Periph_GPIOC
#define SIG_LATCH_PIN				GPIO_Pin_7
#define SIG_LATCH_PINSOURCE			GPIO_PinSource7
#define SIG_LATCH_PIN_AF			GPIO_AF_TIM3

void tim_master_init(void);
