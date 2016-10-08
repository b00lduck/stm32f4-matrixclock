# stm32f4-matrixclock
Use the STM32F4 to drive a large LED matrix with TLC5940



### Port mapping:

 - PA8  GSCLK	common PWM-clock for the TLC5940s

 - PC6  BLANK   common BLANK-signal for the TLC5940s
 - PC7  LATCH   common LATCH-signal for the TLC5940s

 - PD10 SDA		data for one group of TLC5940s
 - PD11 SCK     common SCK for the TLC5940s
 
 - PD12 LED4	discovery board
 - PD13 LED3	discovery board
 - PD14 LED5	discovery board
 - PD15 LED6  	discovery board
