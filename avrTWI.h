/*
 * avrTWI.h
 *
 */ 

#ifndef AVRTWI_H_
#define AVRTWI_H_

// TWI generated status codes
#define TWI_START              0x08 // Start has been transmitted.
#define TWI_REP_START          0x10 // Repeated start has been transmitted.

// TWI master transmitter status codes
#define TWI_MTX_ADR_ACK        0x18 // SLA+W has been transmitted and ACK reveived.
#define TWI_MTX_ADR_NACK       0x20 // SLA+W has been transmitted and NACK reveived.
#define TWI_MTX_DATA_ACK       0x28 // Data byte has been transmitted and ACK reveived.
#define TWI_MTX_DATA_NACK      0x30 // Data byte has been transmitted and NACK reveived.

// TWI master reveiver status codeds
#define TWI_MRX_ADR_ACK        0x40 // SLA+W has been transmitted and ACK reveived.
#define TWI_MRX_ADR_NACK       0x48 // SLA+W has been transmitted and NACK reveived.
#define TWI_MRX_DATA_ACK       0x50 // Data byte has been transmitted and ACK reveived.
#define TWI_MRX_DATA_NACK      0x58 // Data byte has been transmitted and NACK reveived.

#define TWI_ACK  1
#define TWI_NACK 0

void          twi_init(void);
unsigned char twi_start(unsigned char sAdddress) ;
void		  twi_stop(unsigned char sAddress) ;

//TODO
//void          twi_write(uint8_t sla, uint8_t* data, uint8_t length);
//void          twi_read(uint8_t sla, uint8_t* data, uint8_t length);

#endif /* AVRTWI_H_ */