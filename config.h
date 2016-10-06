#pragma once

// STOP_TIMER_ON_DEBUG
//#define STOP_TIMER_ON_DEBUG

/**
 * PLL config
 * See refman page 95ff.
 */
#define PLL_M      8 	// PLL_M: Division factor for the main PLL (PLL) and audio PLL (PLLI2S) input clock
#define PLL_N      336 	// PLL_N: Main PLL (PLL) multiplication factor for VCO
#define PLL_P      2 	// PLL_P: Main PLL division factor for main system clock
#define PLL_Q      7	// PLL_Q: Main PLL division factor for USB OTG FS, SDIO and random number generator clocks


