#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"
#include "tim_master.h"
#include "timing.h"
#include "data_dma.h"
#include "tim_gsclk.h"

void tim_master_init(void) {

	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	// Timer clock enable
	RCC_APB1PeriphClockCmd(SIG_MAIN_TIMER_CLK, ENABLE);

	// GPIO clock enable
	RCC_AHB1PeriphClockCmd(SIG_BLANK_PORT_CLK, ENABLE);

	// GPIO configuration
	GPIO_InitStructure.GPIO_Pin = SIG_BLANK_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(SIG_BLANK_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(SIG_BLANK_PORT, SIG_BLANK_PINSOURCE, SIG_BLANK_PIN_AF);

	GPIO_InitStructure.GPIO_Pin = SIG_LATCH_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(SIG_LATCH_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(SIG_LATCH_PORT, SIG_LATCH_PINSOURCE, SIG_LATCH_PIN_AF);

	// Configure the timer
	// Generate BLANK/LATCH signals and gate for GSCLK

    // Time base configuration
	TIM_TimeBaseStructure.TIM_Prescaler = CLOCK_PRESCALE;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_CenterAligned2;
	TIM_TimeBaseStructure.TIM_Period = 0x1000 + BLANK_LENGTH + DELAY_GSCLK;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(SIG_MAIN_TIMER, &TIM_TimeBaseStructure);

	// PWM1 Mode configuration: Channel1 (BLANK)
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	TIM_OCInitStructure.TIM_Pulse = BLANK_LENGTH;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OC1Init(SIG_MAIN_TIMER, &TIM_OCInitStructure);

	// OC Mode configuration: Channel2 (LATCH)
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	TIM_OCInitStructure.TIM_Pulse = LATCH_LENGTH;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OC2Init(SIG_MAIN_TIMER, &TIM_OCInitStructure);

	// OC Mode configuration: Channel3 (gate for GSCLK)
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	TIM_OCInitStructure.TIM_Pulse = BLANK_LENGTH + DELAY_GSCLK;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OC3Init(SIG_MAIN_TIMER, &TIM_OCInitStructure);
	TIM_SelectOutputTrigger(SIG_MAIN_TIMER, TIM_TRGOSource_OC3Ref);
	TIM_SelectMasterSlaveMode(SIG_MAIN_TIMER, TIM_MasterSlaveMode_Enable);

	// OC Mode configuration: Channel4 (trigger for data transfer)
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	TIM_OCInitStructure.TIM_Pulse = LATCH_LENGTH + DELAY_DATA;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OC4Init(SIG_MAIN_TIMER, &TIM_OCInitStructure);

	// Enable the global interrupts
	NVIC_InitStructure.NVIC_IRQChannel = SIG_MAIN_TIMER_CC_IRQ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 15;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 15;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	// enable interrupts
	TIM_ITConfig(SIG_MAIN_TIMER, TIM_IT_CC4, ENABLE);

	// enable the counter
	TIM_Cmd(SIG_MAIN_TIMER, ENABLE);

	// Main Output Enable
	TIM_CtrlPWMOutputs(SIG_MAIN_TIMER, ENABLE);

}


void TIM3_IRQHandler(void) {

	// Reset GSCLK timer to prevent flapping of off state due to uneven length of GSCLK active period
	SIG_GSCLK_TIMER->CNT = 0;

	// flip video ram buffer
	activeBuffer ^= 1;
	startDma(vram[activeBuffer]);

	frameStart = 1;
	TIM_ClearITPendingBit(SIG_MAIN_TIMER, TIM_IT_CC4);
}

