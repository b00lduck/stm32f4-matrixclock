#include "main.h"

#include "stm32f4xx_dbgmcu.h"

//#include "tools/itoa.h"

#include "tlc5940/driver.h"


void Delay1ms(uint32_t nCount);
volatile uint32_t delay1ms;


void init() {

    // Initialize LEDS GPIO
    SysTick_Config(SystemCoreClock / 1000);
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

	tlc5940_init();

}

int main(void) {

	init();

	// mainloop (TM)
	while (1) {
	    STM_EVAL_LEDToggle(LED3);
	    Delay1ms(100);
	    STM_EVAL_LEDToggle(LED4);
	    Delay1ms(100);
	    STM_EVAL_LEDToggle(LED5);
	    Delay1ms(100);
	    STM_EVAL_LEDToggle(LED6);
	    Delay1ms(100);	    	
	}

}

void SysTick_Handler(void) {
    if(delay1ms) delay1ms--;
}

void Delay1ms(uint32_t nCount) {
    delay1ms = nCount;
    while(delay1ms);
}
