#include "main.h"
#include "driver.h"
#include "data_dma.h"
#include "tim_gsclk.h"
#include "tim_master.h"
#include "videoram.h"

void tlc5940_init(void) {
	tim_gsclk_init();
	tim_master_init();
	data_dma_init();
}
