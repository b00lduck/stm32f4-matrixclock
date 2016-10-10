#pragma once
#include <stdint.h>

#define VIDEORAMSIZE 1000

extern uint8_t vram[VIDEORAMSIZE] __attribute__ ((section (".sram1")));
