#ifndef UART_H
#define UART_H

void uart_init();
void uart_send(char letter);
char uart_read();

void uart_send_str(char ** str);

#endif //!UART_H