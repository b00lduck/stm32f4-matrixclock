#pragma once
#include "stm32f4xx_dma.h"
#include "videoram.h"

#define SIG_DATA_DMA				DMA2

#define SIG_DATA_CHANNEL       		DMA_Channel_7
#define SIG_DATA_STREAM        		DMA2_Stream1
#define SIG_DATA_STREAM_CLOCK 		RCC_AHB1Periph_DMA2
#define SIG_DATA_STREAM_IRQ 		DMA2_Stream1_IRQn

#define SIG_DATA_TIMER				TIM8
#define SIG_DATA_TIMER_CLOCK		RCC_APB2Periph_TIM8

#define SIG_DATA_PORT				GPIOE
#define SIG_DATA_PORT_CLOCK			RCC_AHB1Periph_GPIOE

#define SIG_DATACLOCK_PORT			GPIOC
#define SIG_DATACLOCK_PORT_CLOCK	RCC_AHB1Periph_GPIOC
#define SIG_DATACLOCK_PIN			GPIO_Pin_9
#define SIG_DATACLOCK_PINSOURCE		GPIO_PinSource9
#define SIG_DATACLOCK_PIN_AF		GPIO_AF_TIM8

#define BUFFERSIZE 					(192 * NUMTLCS)

void data_dma_init(void);


static inline void startDma(uint8_t* target) {

	SIG_DATA_PORT->ODR = *target; // set first byte prior starting the clock

	DMA2_Stream1->M0AR = ((uint32_t) target) + 1;
	DMA2_Stream1->NDTR = BUFFERSIZE;

	DMA2_Stream1->CR |= DMA_Channel_7 | DMA_Priority_VeryHigh | DMA_MemoryDataSize_Word | DMA_PeripheralDataSize_Byte |
						DMA_MemoryInc_Enable | DMA_DIR_MemoryToPeripheral | DMA_SxCR_TCIE;

	DMA2_Stream1->CR |= DMA_SxCR_EN;

	// reset the timer
	SIG_DATA_TIMER->CNT = 0;

	// enable the timer
	SIG_DATA_TIMER->CR1 |= TIM_CR1_CEN;
}
