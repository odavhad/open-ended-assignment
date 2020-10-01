#ifndef USART_H
#define	USART_H

#include <xc.h>
#include <pic18f4520.h>

void USART_init(long);
void USART_tx_char(char);
void USART_send_string(const char *);
//char USART_rx_char();

#define F_CPU 8000000/64
#define BAUD_VALUE (((float)(F_CPU)/(float)baud_rate)-1)

#endif	/* USART_H */
