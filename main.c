/*
 * avrTWIscanner.c
 *
 * Created: 12/07/2017 08:06:01
 * Author : Billy
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#include "avrTWI.h"
#include "usart.h"
#include "avrUtil.h"

int main(void)
{
    USART_Init(MYUBRR) ;
	
	USART_Send_string("Initialsing I2C ...\r\n") ;
	twi_init() ;
	
    while (1) 
    {
		unsigned char rTwi ;
		unsigned char slaveAddress ;
	    char          *str ;
		char          aHex[2] ;
		uint8_t       u ;
		
		 USART_Send_string("Searching\r\n") ;
	    for(uint8_t fCnt = 1; fCnt < 128; fCnt++){

		  slaveAddress = fCnt ;
		  rTwi = twi_start(slaveAddress) ;
		  if(!rTwi){
		    
			str = getHexValue(fCnt) ;
		
		    USART_Send_string("I2C device found : ") ;
		    USART_Send_int(fCnt) ;
			USART_Send_string(" Hex value : ") ;
			u = 0 ;
			while (*str) {
		      aHex[u] = *str++ ;
			  u++ ;	  
			}
			
			USART_Send_string("0x") ;
			for(uint8_t i = u; i>0;i--) {
			  USART_Sendbyte(aHex[i-1]);
			}
		    USART_Send_string(" ...\r\n") ;
		     _delay_ms(100) ;
		  }
		  twi_stop(slaveAddress) ;
		  _delay_ms(50) ;	

		}
		_delay_ms(4000) ;
    }
}

