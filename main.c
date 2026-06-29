#include "config.h"
#include "uart.h"
#include "adc.h"
#include "ws2812b.h"
#include "game.h"

int main(void) {
	// Inicjalizacja HW
	TCCR1A &= ~((1 << COM1B1) | (1 << COM1B0));
	LED_DDR |= (1 << LED_PIN);
	BUZZER_DDR |= (1 << BUZZER_PIN);
	DDRC = 0x00;

	UART_init(MYUBRR);
	ADC_init();
	setup_interrupts();
	initRouletteTable();
	sei();

	while(1) {
		switch(aktualnyStan) {
			case STAN_MENU:
			PuTTY_clear();
			printLogo();
			UART_print_P(PSTR("\x1B[18;25HNacisnij Spacje, aby rozpoczac\r\n"));
			_delay_ms(500);
			if (UART_getChar() == ' ') aktualnyStan = STAN_ZAKLAD;
			break;

			case STAN_ZAKLAD:
			PuTTY_clear();
			printZaklad();
			char z = UART_getChar();
			if (z == 'z' || z == 'Z') { wybranyZaklad = ZAKLAD_ZIELONY; aktualnyStan = STAN_PRZYCISK; }
			else if (z == 'c' || z == 'C') { wybranyZaklad = ZAKLAD_CZERWONY; aktualnyStan = STAN_PRZYCISK; }
			else if (z == 'b' || z == 'B') { wybranyZaklad = ZAKLAD_CZARNY; aktualnyStan = STAN_PRZYCISK; }
			break;

			case STAN_PRZYCISK:
			PuTTY_clear();
			UART_print_P(PSTR("\x1B[3;32HZAKLAD PRZYJETY!\r\n"));
			UART_print_P(PSTR("\x1B[7;20HUstaw sile rzutu za pomoca potencjometru\r\n")); 
			UART_print_P(PSTR("\x1B[11;17HNastêpnie,nacisnij fizyczny przycisk do startu\r\n"));
			
			while (!startRoulette) {
				// Czytamy wartoœæ z potencjometru przez nasz modu³ ADC
				uint16_t moc = ADC_read(POT_CHANNEL);
				
				// Rysujemy pasek si³y
				UART_print_P(PSTR("\x1B[15;24HSila rzutu: ["));
				uint8_t kreski = moc / 51;
				for (uint8_t i = 0; i < 20; i++) {
					UART_sendChar(i < kreski ? '#' : ' ');
				}
				UART_print_P(PSTR("]\r")); // \r powraca na pocz¹tek linii, ¿eby pasek siê odœwie¿a³ p³ynnie
				_delay_ms(50);
			}
			startRoulette = false; // Zerujemy flagê startu
			aktualnyStan = STAN_LOSOWANIE;
			break;

			case STAN_LOSOWANIE:
			PuTTY_clear();
			UART_print_P(PSTR("\x1B[12;20HKulka ruszyla, czekaj na wynik zakladu.\r\n"));
			Spin();
			aktualnyStan = STAN_WYNIK;
			break;

			case STAN_WYNIK:
			PuTTY_clear();
			if (ballPos == 0 && wybranyZaklad == ZAKLAD_ZIELONY) {
				UART_print_P(PSTR("\x1B[10;19HGratulacje, wygrales! Wypadl kolor zielony.\r\n"));
			}
			else if (ballPos % 2 == 0 && wybranyZaklad == ZAKLAD_CZERWONY) {
				UART_print_P(PSTR("\x1B[10;18HGratulacje, wygrales! Wypadl kolor czerwony.\r\n"));
			}
			else if (ballPos % 2 == 1 && wybranyZaklad == ZAKLAD_CZARNY) {
				UART_print_P(PSTR("\x1B[10;19HGratulacje, wygrales! Wypadl kolor czarny.\r\n"));
			}
			else {
				UART_print_P(PSTR("\x1B[10;12HNiestety przegrales, moze nastepnym razem ci sie uda :)\r\n"));
			}

			UART_print_P(PSTR("\x1B[14;10HKoniec Gry! Nacisnij dowolny klawisz, aby powrocic do menu."));
			UART_getChar();
			aktualnyStan = STAN_MENU;
			break;
		}
	}
}