#pragma once

// master and GSCLK timer settings
#define CLOCK_PRESCALE 0x0020   // prescaler of the master and GSCLK timer
#define DELAY_GSCLK 0x001       // wait n cycles after BLANK falls for GSCLK start
#define BLANK_LENGTH 0x0004     // length of BLANK impulse
#define LATCH_LENGTH 0x0002     // length of LATCH impulse
#define DELAY_DATA 0x0001		// wait n cycles after LATCH falls for DMA start

// DMA settings
#define DMA_PERIOD 80			// DMA speed (inverse)
