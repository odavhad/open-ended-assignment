#include <xc.h>
#include <pic18f4520.h>
#include "conbits.h"
#include "usart.h"

volatile int flag;

__interrupt(high_priority) void myISR(void) {
    if(INTCON3bits.INT1IF == 1) {
        flag = 1;
        
        INTCON3bits.INT1IF = 0;
    }
}

void main(void) { 
    // initialize flag
    flag = 0;
    
    // set input bits    
    TRISBbits.TRISB0 = 1;   
    TRISBbits.TRISB5 = 1;
    TRISBbits.TRISB6 = 1;
    TRISBbits.TRISB7 = 1;
    
    USART_init(9600);
    
    // set internal oscillator freq = 8MHz
    OSCCON = 0x72;   
    
    // enable interrupt priority    
    RCONbits.IPEN = 1;
    
    // enable high priority global interrupt
    INTCONbits.GIEH = 1;
        
    // enable INT1 interrupt
    INTCON3bits.INT1IE=1; 
    // clear INT1 interrupt flag
    INTCON3bits.INT1IF=0;                       
    // set INT1 interrupt priority as high
    INTCON3bits.INT1IP=1;  
    
    while(1) {
        if(flag == 1) {
            if(PORTBbits.RB5 == 1) {
                // 1xx
                if(PORTBbits.RB6 == 1) {
                    // 11x
                    if(PORTBbits.RB7 == 1) {
                        // 111
                        USART_send_string("ATA\r");
                    } else {
                        // 110
                        USART_send_string("ATH\r");
                    }
                } else {
                    // 10x
                    if(PORTBbits.RB7 == 1) {
                        // 101
                        USART_send_string("ATD+ +917020122346\r");
                    } else {
                        // 100
                        USART_send_string("AT+CGSN\r");
                    }
                }
            } else {
                // 0xx
                if(PORTBbits.RB6 == 1) {
                    // 01x
                    if(PORTBbits.RB7 == 1) {
                        // 011
                        USART_send_string("AT+COPS?\r");
                    } else {
                        // 010
                        USART_send_string("AT+CSQ\r");
                    }
                } else {
                    // 00x
                    if(PORTBbits.RB7 == 1) {
                        // 001
                        USART_send_string("ATE0\r");
                    }
                }
            }
        }
    }
}
