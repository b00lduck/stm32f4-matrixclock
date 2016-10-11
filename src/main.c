#include "main.h"
#include "stm32f4xx_dbgmcu.h"
#include "tlc5940/videoram.h"
#include "tlc5940/driver.h"

void init() {

    // Initialize LEDS GPIO
    // SysTick_Config(SystemCoreClock / 1000);
    STM_EVAL_LEDInit(LED3);
    STM_EVAL_LEDInit(LED4);
    STM_EVAL_LEDInit(LED5);
    STM_EVAL_LEDInit(LED6);

    // Initialize button GPIO
    //STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_EXTI);

    // Timer stop on debug
    #ifdef STOP_TIMER_ON_DEBUG
	DBGMCU_APB1PeriphConfig(DBGMCU_TIM1_STOP,ENABLE);
	DBGMCU_APB1PeriphConfig(DBGMCU_TIM8_STOP,ENABLE);
	DBGMCU_Config(DBGMCU_TIM3_STOP,ENABLE);
    #endif

	memset(vram, 0x00, VIDEORAMSIZE * 2);

	tlc5940_init();

}


int main(void) {

	init();

	// mainloop (TM)
	while (1) {

		while (frameStart == 0) {
			STM_EVAL_LEDOff(LED3);
		}

		STM_EVAL_LEDOn(LED3);

		convertFrame();

		STM_EVAL_LEDOff(LED3);

		frameStart = 0;

	}

}
