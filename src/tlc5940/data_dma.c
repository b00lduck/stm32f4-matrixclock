#include "data_dma.h"
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_dma.h"
#include "videoram.h"
#include "timing.h"


void data_dma_init() {

	GPIO_InitTypeDef GPIO_InitStructure;

	// GPIO clock
	RCC_AHB1PeriphClockCmd(SIG_DATA_PORT_CLOCK, ENABLE);

	// GPIO
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(SIG_DATA_PORT, &GPIO_InitStructure);

	// GPIO clock enable
	RCC_AHB1PeriphClockCmd(SIG_DATACLOCK_PORT_CLOCK, ENABLE);

	// GPIO configuration
	GPIO_InitStructure.GPIO_Pin = SIG_DATACLOCK_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(SIG_DATACLOCK_PORT, &GPIO_InitStructure);

	// Connect pin to alternate function of TIM8
	GPIO_PinAFConfig(SIG_DATACLOCK_PORT, SIG_DATACLOCK_PINSOURCE, SIG_DATACLOCK_PIN_AF);


	DMA_InitTypeDef  DMA_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	// Enable Timer Clock
	RCC_APB2PeriphClockCmd(SIG_DATA_TIMER_CLOCK, ENABLE);

	// Enable DMA Clock
	RCC_AHB1PeriphClockCmd(SIG_DATA_STREAM_CLOCK, ENABLE);

	// Time base configuration
	TIM_TimeBaseStructure.TIM_Prescaler = TIM_ICPSC_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = DMA_PERIOD;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(SIG_DATA_TIMER, &TIM_TimeBaseStructure);

	// Be a slave of TIM1
	TIM_SelectInputTrigger(SIG_DATA_TIMER, TIM_TS_ITR0);
    TIM_SelectSlaveMode(SIG_DATA_TIMER, TIM_SlaveMode_Trigger);
    TIM_SelectMasterSlaveMode(SIG_DATA_TIMER, TIM_MasterSlaveMode_Enable);


    // SCK output: PWM1 Mode configuration: Channel3
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	TIM_OCInitStructure.TIM_Pulse = DMA_PERIOD >> 1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
    TIM_OC4Init(SIG_DATA_TIMER, &TIM_OCInitStructure);

	// Main Output Enable
	TIM_CtrlPWMOutputs(SIG_DATA_TIMER, ENABLE);

	// use timer update trigger for pixel DMA
	TIM_DMACmd(SIG_DATA_TIMER, TIM_DMA_Update, ENABLE);

	// Configure DMA Stream
	DMA_InitStructure.DMA_Channel = SIG_DATA_CHANNEL;
	DMA_InitStructure.DMA_PeripheralBaseAddr = ((uint32_t)&SIG_DATA_PORT->ODR);
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)vram;
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	DMA_InitStructure.DMA_BufferSize = BUFFERSIZE;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(SIG_DATA_STREAM, &DMA_InitStructure);

    DMA_Cmd(SIG_DATA_STREAM, DISABLE);


    // Enable DMA Stream Transfer Complete interrupt
    DMA_ITConfig(SIG_DATA_STREAM, DMA_IT_TCIF1, ENABLE);

    // Enable the global Interrupt
    NVIC_InitStructure.NVIC_IRQChannel = SIG_DATA_STREAM_IRQ;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 15;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 15;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

}


void DMA2_Stream1_IRQHandler(void) {

	// Clear interrupt flag.
	DMA2->LIFCR |= DMA_LIFCR_CTCIF1;

	// blank out
	SIG_DATA_PORT->ODR = 0x00;

	// disable the timer
	SIG_DATA_TIMER->CR1 &= ~TIM_CR1_CEN;

}


