#pragma once

#define SIG_GSCLK_PORT				GPIOA
#define SIG_GSCLK_PORT_CLK    		RCC_AHB1Periph_GPIOA
#define SIG_GSCLK_PIN				GPIO_Pin8
#define SIG_GSCLK_PINSOURCE			GPIO_PinSource8
#define SIG_GSCLK_PIN_AF			GPIO_AF_TIM1

#define SIG_GSCLK_TIMER				TIM1
#define SIG_GSCLK_TIMER_CLK			RCC_APB2Periph_TIM1


void tim_gsclk_init(void);
