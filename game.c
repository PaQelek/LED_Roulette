#include "game.h"
#include "ws2812b.h"
#include "adc.h"
#include "uart.h"

// Zmienne
volatile bool startRoulette = false;
StanyGry aktualnyStan = STAN_MENU;
uint8_t ballPos = 1;
uint8_t wybranyZaklad = ZAKLAD_NONE;

// Przerwanie
ISR(INT0_vect) {
	startRoulette = true;
}

void setup_interrupts(void) {
	DDRD &= ~(1 << DDD2); // Konfiguracja linii D2 jako wejœcie dla przycisku INT0
	EICRA |= (1 << ISC01); // Konfiguracja przerwania na zbocze opadaj¹ce (FALLING)
	EICRA &= ~(1 << ISC00);
	EIMSK |= (1 << INT0);  // Aktywacja maski przerwania INT0
}

void playMetallicClick(void) {
	uint16_t period = 50;
	for (uint8_t i = 0; i < 15; i++) {
		BUZZER_PORT |= (1 << BUZZER_PIN);
		delay_var_us(period);
		BUZZER_PORT &= ~(1 << BUZZER_PIN);
		delay_var_us(period);
		
		period += 40;
	}
	BUZZER_PORT &= ~(1 << BUZZER_PIN);
}

void MoveOne(void) {
	// Przywrócenie pierwotnego koloru t³a dla diody, na której sta³a wirtualna kulka
	if (ballPos == 0) {
		leds[0] = (Color){0, BRIGHTNESS, 0};
		} else if (ballPos % 2 == 0) {
		leds[ballPos] = (Color){BRIGHTNESS, 0, 0};
		} else {
		leds[ballPos] = (Color){0, 0, BRIGHTNESS};
	}

	// Przesuniêcie pozycji wirtualnej kulki o jeden krok w przód
	ballPos++;
	if (ballPos >= NUM_LEDS) ballPos = 0;
	
	// Ustawienie koloru nowej pozycji kulki na bia³y (R+G+B)
	leds[ballPos].r = BRIGHTNESS;
	leds[ballPos].g = BRIGHTNESS;
	leds[ballPos].b = BRIGHTNESS;

	display();
	playMetallicClick();
	_delay_ms(2);
}

void Spin(void) {
	uint16_t adc_val = ADC_read(POT_CHANNEL);
	
	// Mapowanie ADC na mno¿nik zwalniania. Im wiêksza wartoœæ potencjometru, tym silniejszy rzut.
	float slowdownModifier = 1.07 + ((float)adc_val / 1023.0) * 0.03;
	float currentDelay = 10.0;

	while (currentDelay < 500.0) {
		MoveOne();
		for(int i = 0; i < (int)currentDelay; i++) {
			_delay_ms(1);
		}
		currentDelay *= slowdownModifier;
	}
	_delay_ms(3000); // Zatrzymanie na wyniku przez 3 sekundy
}

void initRouletteTable() {
	leds[0] = (Color){0, BRIGHTNESS, 0};
	for (uint8_t i = 1; i < NUM_LEDS; i += 2) leds[i] = (Color){0, 0, BRIGHTNESS};
	for (uint8_t i = 2; i < NUM_LEDS; i += 2) leds[i] = (Color){BRIGHTNESS, 0, 0};
	display();
}

void delay_var_us(volatile uint16_t us) {
	while(us--) __builtin_avr_delay_cycles(16);
}