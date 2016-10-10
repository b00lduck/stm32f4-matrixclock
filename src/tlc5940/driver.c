#include "main.h"
#include "driver.h"
#include "data_dma.h"
#include "tim_gsclk.h"
#include "tim_master.h"
#include "videoram.h"

void putPixel(uint8_t x, uint8_t y, uint8_t c);

void tlc5940_init(void) {
	tim_gsclk_init();
	tim_master_init();
	data_dma_init();

	memset(vram, 0, VIDEORAMSIZE);

	putPixel(7, 0, 0);
	putPixel(6, 0, 32);
	putPixel(5, 0, 64);
	putPixel(4, 0, 96);
	putPixel(3, 0, 128);
	putPixel(2, 0, 160);
	putPixel(1, 0, 192);
	putPixel(0, 0, 255);

	putPixel(8, 0, 0);
	putPixel(9, 0, 32);
	putPixel(10, 0, 64);
	putPixel(11, 0, 96);
	putPixel(12, 0, 128);
	putPixel(13, 0, 160);
	putPixel(14, 0, 192);
	putPixel(15, 0, 255);


}

void putPixel(uint8_t x, uint8_t y, uint8_t c) {

	vram[x * 12]     = (c & 0b10000000) >> 7;
	vram[x * 12 + 1] = (c & 0b1000000) >> 6;
	vram[x * 12 + 2] = (c & 0b100000) >> 5;
	vram[x * 12 + 3] = (c & 0b10000) >> 4;
	vram[x * 12 + 4] = (c & 0b1000) >> 3;
	vram[x * 12 + 5] = (c & 0b100) >> 2;
	vram[x * 12 + 6] = (c & 0b10) >> 1;
	vram[x * 12 + 7] = c & 0b1;

}


