/*
*
*
*
*
*/
#ifndef USART_H_
#define USART_H_

#define F_CPU   16000000UL                    // Clock Speed
#define BAUD    9600	                      // Baud Rate
#define MYUBRR  ((F_CPU / (16L * BAUD)) - 1)  // Per the datasheet 1x
//#define MYUBRR  ((F_CPU / (8L * BAUD)) - 1)   // Per the datasheet 2x

void USART_Init(unsigned int ubrr);

void          USART_Sendbyte   (unsigned char data );
void          USART_Send_string(const char *str);
void          USART_Send_int   (unsigned int d);

unsigned char USART_Receive    (void);

#endif /* USART_H_ */