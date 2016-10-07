#include "main.h"
#include "driver.h"

void tlc5940_init(void) {

	// TIM1 clock enable
	RCC_APB2PeriphClockCmd(SIG_BLANK_TIMER_CLK, ENABLE);

	// GPIO clock enable
	RCC_AHB1PeriphClockCmd(SIG_BLANK_PORT_CLK, ENABLE);

	// GPIO configuration
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(SIG_BLANK_PORT, &GPIO_InitStructure);

	// Connect PIN8 of PORT A to alternate function (TIM1)
	GPIO_PinAFConfig(SIG_BLANK_PORT, SIG_BLANK_PINSOURCE, SIG_BLANK_PIN_AF);


	// Configure the timer
	// Generate BLANK signals
	// Trigger TIM3 (GSCLK generation)

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_BDTRInitTypeDef TIM_BDTRInitStructure;
	//NVIC_InitTypeDef NVIC_InitStructure;

	// Time base configuration
	TIM_TimeBaseStructure.TIM_Prescaler = 0x0010;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = 0xaae6;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV4;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(SIG_BLANK_TIMER, &TIM_TimeBaseStructure);

	// PWM1 Mode configuration: Channel1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	TIM_OCInitStructure.TIM_Pulse = 1000;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OC1Init(SIG_BLANK_TIMER, &TIM_OCInitStructure);

	/*
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	TIM_OCInitStructure.TIM_Pulse = HSYNC_TIMER_CC2;
	TIM_OC2Init(HSYNC_TIMER, &TIM_OCInitStructure);
	*/

	// Master Mode for TIM3
	/*
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = pixelDmaStartOffset;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OC4Init(HSYNC_TIMER, &TIM_OCInitStructure);
    TIM_SelectOutputTrigger(HSYNC_TIMER,  TIM_TRGOSource_OC4Ref);
    */

	/*
	// Be a slave of TIM3
	TIM_SelectInputTrigger(HSYNC_TIMER, TIM_TS_ITR2);
	//TIM_SelectSlaveMode(SIG_BLANK_TIMER, TIM_SlaveMode_Trigger);

    // Enable MS Mode
    TIM_SelectMasterSlaveMode(HSYNC_TIMER, TIM_MasterSlaveMode_Enable);
    */

/*

	// Automatic Output enable, Break, dead time and lock configuration
	TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
	TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
	TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_OFF;
	TIM_BDTRInitStructure.TIM_DeadTime = 0;
	TIM_BDTRInitStructure.TIM_Break = TIM_Break_Disable;
	TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;
	TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
    TIM_BDTRConfig(SIG_BLANK_TIMER, &TIM_BDTRInitStructure);
*/
    /*
	// Enable the global Interrupt
	NVIC_InitStructure.NVIC_IRQChannel = HSYNC_TIMER_CC_IRQ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	*/

	// Interrupts enable
	//TIM_ITConfig(HSYNC_TIMER, TIM_IT_CC2, ENABLE);

	// enable the counter
	TIM_Cmd(SIG_BLANK_TIMER, ENABLE);

	// Main Output Enable
	TIM_CtrlPWMOutputs(SIG_BLANK_TIMER, ENABLE);
}



/*
void TIM1_CC_IRQHandler(void) {

	if (videoInstance.textMode == 1) {
		HsyncIsrTextMode();
	} else {
		HsyncIsrPixelMode();
	}

	// reset interrupt flag
	HSYNC_TIMER->SR = (uint16_t)~TIM_IT_CC2;

	// increment line
	videoInstance.current_y++;

	for(uint8_t i=0; i < videoInstance.switchToBwAtLineSize; i++) {
		if(videoInstance.current_y == videoInstance.switchToBwAtLine[i]) {
			VIDEO_SWITCH_PORT->BSRRL = GPIO_Pin_1;
		}
	}

	for(uint8_t i=0; i < videoInstance.switchToColorAtLineSize; i++) {
		if(videoInstance.current_y == videoInstance.switchToColorAtLine[i]) {
			VIDEO_SWITCH_PORT->BSRRH = GPIO_Pin_1;
		}
	}

}
*/

