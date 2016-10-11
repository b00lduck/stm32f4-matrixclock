#pragma once
#include <stdint.h>


#define NUMTLCS 8
#define REALVIDEORAMSIZE (NUMTLCS * 16)
#define VIDEORAMSIZE (NUMTLCS * 192)


extern uint8_t vram[2][VIDEORAMSIZE] __attribute__ ((section (".sram1")));
extern uint8_t realvram[REALVIDEORAMSIZE];

extern uint8_t frameStart;
extern uint8_t activeBuffer;

void convertFrame(void);


