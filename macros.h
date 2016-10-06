#pragma once

/**
 * Deliver random number 32 bit
 */
static uint32_t random32 = 314159265;
static inline uint32_t xorshift32() {
	random32 ^= random32 << 13;
	random32 ^= random32 >> 17;
	random32 ^= random32 << 5;
	return random32;
}

