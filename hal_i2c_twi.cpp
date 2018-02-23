#include <stdint.h>
#include <avr/io.h>
#include <util/twi.h>
#include "hal_i2c_twi.h"


c_i2c::c_i2c()
{
    
}


void c_i2c::init(uint32_t f_cpu, uint32_t f_i2c = 100000u)
{
    // Prescaler is not used. 
    TWSR = 0x00u;
    TWBR = ((f_cpu / f_i2c) - 16u) / 2u;
    //enable TWI
    TWCR = (1u << TWEN);
}


void c_i2c::transfer_begin(uint8_t slave_address)
{
    TWCR = (1u << TWINT) | (1u << TWSTA) | (1u << TWEN);

    while (0x00u == (TWCR & (1 << TWINT)))
    {

    }

    send_byte(slave_address << 1u);
}


void c_i2c::send_byte(uint8_t byte)
{
    TWDR = byte;
    TWCR = (1u << TWINT) | (1u << TWEN);

    while (0x00u == (TWCR & (1u << TWINT)))
    {

    }
}


uint8_t c_i2c::receive_byte(i2c_receive_response_t send_ack)
{
    TWCR = TWINT | TWEN;

    TWCR = (1u << TWINT) | (1u << TWEN);

    if (ACK == send_ack)
    {
        TWCR |= TWEA;
    }
    
    while (0x00u == (TWCR & (1<<TWINT)))
    {

    }
    return TWDR;
}


void c_i2c::transfer_end(void)
{
    TWCR = (1u << TWINT) | (1u << TWSTO) | (1u << TWEN);
}


uint8_t c_i2c::status(void)
{
    return (uint8_t)(TWSR & 0xF8);
}
