#include "uart.h"

void UART_init(unsigned int ubrr) {
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;
	UCSR0B = (1 << TXEN0) | (1 << RXEN0); // Aktywacja RX i TX
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // Format ramki: 8N1 (8 bitów danych, brak parzystoœci, 1 bit stopu)
}

void UART_sendChar(char data) {
	while(!(UCSR0A & (1 << UDRE0))); // Czekaj na opró¿nienie bufora nadawczego
	UDR0 = data;
}

void UART_print(const char* str) {
	while (*str) {
		UART_sendChar(*str++);
	}
}

void UART_print_P(const char* str) {
	char c;
	while ((c = pgm_read_byte(str))) {
		UART_sendChar(c);
		str++;
	}
}

char UART_getChar(void) {
	while(!(UCSR0A & (1 << RXC0))); // Blokuj¹ce oczekiwanie na odebranie bajtu bajtu
	return UDR0;
}

void PuTTY_clear(void) {
	UART_print_P(PSTR("\x1B[2J\x1B[H")); // Wyczyszczenie okna terminala i powrót kursora
}

void printLogo(void) {
	UART_print_P(PSTR("\x1B[4C /$$$$$$$  /$$   /$$ /$$       /$$$$$$$$ /$$$$$$$$ /$$   /$$  /$$$$$$ \r\n"));
	UART_print_P(PSTR("\x1B[4C| $$__  $$| $$  | $$| $$      | $$_____/|__  $$__/| $$  /$$/ /$$__  $$\r\n"));
	UART_print_P(PSTR("\x1B[4C| $$  \\ $$| $$  | $$| $$      | $$         | $$   | $$ /$$/ | $$  \\ $$\r\n"));
	UART_print_P(PSTR("\x1B[4C| $$$$$$$/| $$  | $$| $$      | $$$$$      | $$   | $$$$$/  | $$$$$$$$\r\n"));
	UART_print_P(PSTR("\x1B[4C| $$__  $$| $$  | $$| $$      | $$__/      | $$   | $$  $$  | $$__  $$\r\n"));
	UART_print_P(PSTR("\x1B[4C| $$  \\ $$| $$  | $$| $$      | $$         | $$   | $$\\  $$ | $$  | $$\r\n"));
	UART_print_P(PSTR("\x1B[4C| $$  | $$|  $$$$$$/| $$$$$$$$| $$$$$$$$   | $$   | $$ \\  $$| $$  | $$\r\n"));
	UART_print_P(PSTR("\x1B[4C|__/  |__/ \\______/ |________/|________/   |__/   |__/  \\__/|__/  |__/\r\n"));
}

void printZaklad(void) {
	UART_print_P(PSTR("\x1B[13;30HWYBIERZ SWOJ ZAKLAD:"));
	UART_print_P(PSTR("\x1B[18;9HKolor Zielony"));
	UART_print_P(PSTR("\x1B[21;9H#############"));
	UART_print_P(PSTR("\x1B[22;9H#           #"));
	UART_print_P(PSTR("\x1B[23;9H# Klawisz Z #"));
	UART_print_P(PSTR("\x1B[24;9H#           #"));
	UART_print_P(PSTR("\x1B[25;9H#############"));
	UART_print_P(PSTR("\x1B[18;33HKolor Czerwony"));
	UART_print_P(PSTR("\x1B[21;33H#############"));
	UART_print_P(PSTR("\x1B[22;33H#           #"));
	UART_print_P(PSTR("\x1B[23;33H# Klawisz C #"));
	UART_print_P(PSTR("\x1B[24;33H#           #"));
	UART_print_P(PSTR("\x1B[25;33H#############"));
	UART_print_P(PSTR("\x1B[18;56HKolor Czarny"));
	UART_print_P(PSTR("\x1B[21;56H#############"));
	UART_print_P(PSTR("\x1B[22;56H#           #"));
	UART_print_P(PSTR("\x1B[23;56H# Klawisz B #"));
	UART_print_P(PSTR("\x1B[24;56H#           #"));
	UART_print_P(PSTR("\x1B[25;56H#############"));
}