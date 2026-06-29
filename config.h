#ifndef CONFIG_H_
#define CONFIG_H_

#define F_CPU 16000000UL
#define BAUD 9600
#define MYUBRR (F_CPU / 16 / BAUD - 1)

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <stdbool.h>

// --- PINOUT ---
#define LED_PIN         PB1     // D9
#define BUZZER_PIN      PB2     // D10
#define LED_PORT        PORTB
#define LED_DDR         DDRB
#define BUZZER_PORT     PORTB
#define BUZZER_DDR      DDRB

// --- PARAMETRY GRY ---
#define NUM_LEDS        16
#define BRIGHTNESS      40
#define POT_CHANNEL     1       // A1

#define ZAKLAD_NONE     0
#define ZAKLAD_ZIELONY  1
#define ZAKLAD_CZERWONY 2
#define ZAKLAD_CZARNY   3

#endif