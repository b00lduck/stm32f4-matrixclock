#include "videoram.h"

uint8_t vram[VIDEORAMSIZE] __attribute__ ((section (".sram1")));
