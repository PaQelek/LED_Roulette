#include "adc.h"

void ADC_init(void) {
	ADMUX = (1 << REFS0); // Odniesienie do napiêcia AVCC z kondensatorem filtruj¹cym na AREF
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // W³¹czenie ADC + Preskaler 128
}

uint16_t ADC_read(uint8_t channel) {
	ADMUX = (ADMUX & 0xF0) | (channel & 0x0F); // Wybór kana³u ADC
	ADCSRA |= (1 << ADSC); // Start konwersji
	while (ADCSRA & (1 << ADSC)); // Oczekiwanie na flagê koñca konwersji
	return ADCW;
}