#include "usart.h"

void USART_init(long baud_rate) {
    float temp;

    TRISC6 = 0;
    TRISC7 = 1;

    temp = BAUD_VALUE;

    SPBRG = (int)temp;
    TXSTA = 0x20;
    RCSTA = 0x90;
}

void USART_tx_char(char out) {
    while(TXIF == 0);
    TXREG = out;
}

//char USART_rx_char() {
//    while(RCIF == 0);
//
//    if(RCSTAbits.OERR) {
//        CREN = 0;
//        NOP();
//        CREN = 1;
//    }
//
//    return RCREG;
//}

void USART_send_string(const char *out) {
    while(*out != '\0') {
        USART_tx_char(*out);
        out++;
    }
}
