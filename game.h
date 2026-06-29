#ifndef GAME_H_
#define GAME_H_
#include "config.h"

typedef enum {
	STAN_MENU, STAN_ZAKLAD, STAN_PRZYCISK, STAN_LOSOWANIE, STAN_WYNIK
} StanyGry;

extern volatile bool startRoulette;
extern StanyGry aktualnyStan;
extern uint8_t ballPos;
extern uint8_t wybranyZaklad;

void delay_var_us(volatile uint16_t us);
void setup_interrupts(void);
void playMetallicClick(void);
void MoveOne(void);
void Spin(void);
void initRouletteTable(void);

#endif