# stm32f4-matrixclock
Use the STM32F4 to drive a large LED matrix with TLC5940



### Port mapping:

 - PA8  GSCLK	common PWM-clock for the TLC5940s    (TIM1 AF1)

 - PC6  BLANK   common BLANK-signal for the TLC5940s (TIM3 AF2)
 - PC7  LATCH   common LATCH-signal for the TLC5940s (TIM3 AF2)
 - PC9  SCK     common LATCH-signal for the TLC5940s (TIM8 AF3)

 - PD12 LED4	discovery board
 - PD13 LED3	discovery board
 - PD14 LED5	discovery board
 - PD15 LED6  	discovery board

 - PE0  SDA_A	Sector A data (DMA)
 - PE1  SDA_B	Sector B data (DMA)
 - PE2  SDA_C	Sector C data (DMA)
 - PE3  SDA_D	Sector D data (DMA)
 - PE4  SDA_E	Sector E data (DMA)
 - PE5  SDA_F	Sector F data (DMA)
 - PE6  SDA_G	Sector G data (DMA)
 - PE7  SDA_H	Sector H data (DMA)
 
 