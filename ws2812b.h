#ifndef WS2812B_H_
#define WS2812B_H_
#include "config.h"

typedef struct {
	uint8_t r;
	uint8_t g;
	uint8_t b;
} Color;

extern Color leds[NUM_LEDS];

void display(void);
void sendByte(uint8_t byte);

#endif