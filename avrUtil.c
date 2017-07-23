/*
 * avrUtil.c
 *
 * Created: 12/07/2017 16:32:50
 *  Author: Billy
 */ 

#include <avr/io.h>
#include <stdlib.h>

#include "usart.h"
#include "avrUtil.h"

char *getHexValue(uint8_t dValue)
{
	static char    hexadecimalnum[3] ;    //static so can use pointer
	int            j = 0 ;
	uint8_t        remainder ;
	uint8_t        quotient ;
	
	quotient = dValue ;
		
	while(quotient != 0){
		       
      remainder = quotient % 16;
	  if (remainder < 10)
	    hexadecimalnum[j++] = 48 + remainder;
		else
      hexadecimalnum[j++] = 55 + remainder;
	  //
      quotient = quotient / 16;
	}
   
	return hexadecimalnum;
}