#ifndef USART_UTILS_H
#define USART_UTILS_H
#endif

#include <stdint.h>

// Funciones necesarias para la entrada serial.

void welcome_message(void);
void setup_USART(uint32_t baudrate);
void send_USART(uint8_t c);
void put_string_USART(char *string);
void read_command(void);