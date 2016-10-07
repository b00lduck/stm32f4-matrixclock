#include "main.h"
#include "driver.h"



void tlc5940_init(void) {
	tim1_init();
	tim3_init();
}



void tim1_init(void) {


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
	TIM_TimeBaseStructure.TIM_Prescaler = 0x00a0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = 0x103c;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV4;
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(SIG_BLANK_TIMER, &TIM_TimeBaseStructure);

	// PWM1 Mode configuration: Channel1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
	TIM_OCInitStructure.TIM_Pulse = 50;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OC1Init(SIG_BLANK_TIMER, &TIM_OCInitStructure);

	// enable the counter
	TIM_Cmd(SIG_BLANK_TIMER, ENABLE);

	// Main Output Enable
	TIM_CtrlPWMOutputs(SIG_BLANK_TIMER, ENABLE);
}

void tim3_init(void) {

	GPIO_InitTypeDef GPIO_InitStructure;

	// Timer clock enable
	RCC_APB1PeriphClockCmd(SIG_GSCLK_TIMER_CLK, ENABLE);

	// GPIO clock enable
	RCC_AHB1PeriphClockCmd(SIG_GSCLK_PORT_CLK, ENABLE);

	// GPIO configuration
	GPIO_InitStructure.GPIO_Pin = SIG_GSCLK_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(SIG_GSCLK_PORT, &GPIO_InitStructure);

	GPIO_PinAFConfig(SIG_GSCLK_PORT, SIG_GSCLK_PINSOURCE, SIG_GSCLK_PIN_AF);


	// Configure the timer
	// Generate GSCLK signals

	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	// Time base configuration
	TIM_TimeBaseStructure.TIM_Prescaler = 0x00a0;
	TIM_TimeBaseStructure.TIM_Period = 0x0002;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV4;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(SIG_GSCLK_TIMER, &TIM_TimeBaseStructure);

	// PWM1 Mode configuration: Channel1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0x0001;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(SIG_GSCLK_TIMER, &TIM_OCInitStructure);

	// enable the counter
	TIM_Cmd(SIG_GSCLK_TIMER, ENABLE);


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

