/*
 * avrTWI.c
 *
 * Created: 11/07/2017 10:17:18
 *  Author: Billy
 */ 

#define F_CPU   16000000UL                    // Clock Speed

#include <avr/io.h>
#include <avr/interrupt.h>
//#include <util/delay.h>
#include <util/twi.h>

#include "avrTWI.h"

static volatile uint8_t twi_buffer[128];
static volatile uint8_t twi_pointer;
static volatile uint8_t twi_length;

#define  MAX_TWI_TRY    0x14

/* I2C clock in Hz */
#define SCL_CLOCK       100000L

/* I2C timer max delay */
#define TWI_TIMER_DELAY 0xFF

void twi_init(void)
{
	// SCL freq = (CPU Clock) / (16 + 2(TWBR) * (prescale value))
	// 400 kHz = (16MHz) / (16 + 2(12) * (1))
    
	TWSR = 0;                         /* no prescaler */
    TWBR = ((F_CPU/SCL_CLOCK)-16)/2;  /* must be > 10 for stable operation */
/*
    TWCR - Control register
	  TWEN           // TWI enable interface and release TWI pins.
	  TWIE           // TWI interrupt.
      TWINT          // TWI interrupt flag
	  TWEA           // TWI Enable acknowledge
	  TWSTA          // TWI Start condition
	  TWSTO          // TWI Stop condition
	  TWWC           // TWI Write condition
*/
}

// From atmega 328 datasheet (page 216)
unsigned char twi_start(unsigned char sAddress)
{
	uint32_t twi_timer = 0 ;
	
	// Send START condition
	TWCR = (1 << TWEN) |        // Enable interface and release TWI pins.
	       (1 << TWINT) |       // Clear the interrupt flag.
	       (1 << TWSTA) ;       // Enable start condition.
	
	// Wait for TWINT flag set
	twi_timer = TWI_TIMER_DELAY ;
	while(!(TWCR & (1<<TWINT)) && twi_timer--) ;	
	  if(twi_timer==0) return 9 ;

    // Check TWI status (Start and repeat start)
	if(((TWSR & TW_NO_INFO) != TW_START) && 
	   ((TWSR & TW_NO_INFO) != TW_REP_START)) return 8 ;
	
	// Load Slave address (Upper 7 bit - value on datasheet)
	TWDR = sAddress<<1 ;
	TWCR = (1<<TWINT) | 
	       (1<<TWEN) ;

    // Wait for TWINT flag set 
	twi_timer = TWI_TIMER_DELAY ;
	while(!(TWCR & (1<<TWINT)) && twi_timer--) ;
	  if(twi_timer==0) return 7 ;

    // Check TWI status (Write and Read acknowledge) 
	if(((TWSR & TW_NO_INFO) != TW_MT_SLA_ACK) &&
	   ((TWSR & TW_NO_INFO) != TW_MR_SLA_ACK)) return 6 ;

    //Ready to transmit data
	return 0 ;
	
}


void twi_stop(unsigned char sAddress)
{
	uint32_t twi_timer = 0 ;
	
	TWCR = (1 << TWEN) |        // Enable interface and release TWI pins.
	       (1 << TWINT) |       // Clear the interrupt flag.
	       (1 << TWSTO) ;       // Enable stop condition.
	
	twi_timer = TWI_TIMER_DELAY ;
	while((TWCR & (1<<TWSTO)) && twi_timer--) ;	
	
}
