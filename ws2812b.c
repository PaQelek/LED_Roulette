#include "ws2812b.h"

Color leds[NUM_LEDS];

void sendByte(uint8_t byte) {
	for (int8_t bit = 7; bit >= 0; bit--) {
		if (byte & (1 << bit)) {
			LED_PORT |= (1 << LED_PIN);
			__builtin_avr_delay_cycles(8);
			LED_PORT &= ~(1 << LED_PIN);
			__builtin_avr_delay_cycles(7);
			} else {
			LED_PORT |= (1 << LED_PIN);
			__builtin_avr_delay_cycles(2);
			LED_PORT &= ~(1 << LED_PIN);
			__builtin_avr_delay_cycles(10);
		}
	}
}

void display(void) {
	cli();
	for (int i = 0; i < NUM_LEDS; i++) {
		sendByte(leds[i].g);
		sendByte(leds[i].r);
		sendByte(leds[i].b);
	}
	sei();
	_delay_us(80);
}