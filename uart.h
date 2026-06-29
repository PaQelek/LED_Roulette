#ifndef UART_H_
#define UART_H_
#include "config.h"

void UART_init(unsigned int ubrr);
void UART_sendChar(char data);
void UART_print_P(const char* str);
char UART_getChar(void);
void PuTTY_clear(void);
void printLogo(void);
void printZaklad(void);

#endif