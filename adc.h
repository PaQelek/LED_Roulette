#ifndef ADC_H_
#define ADC_H_
#include "config.h"

void ADC_init(void);
uint16_t ADC_read(uint8_t channel);

#endif