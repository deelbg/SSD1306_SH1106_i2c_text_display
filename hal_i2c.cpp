#include <stdint.h>
#include "hal_i2c.h"

#define USE_ARDUINO false

#if USE_ARDUINO
    #include <Wire.h>
#else
    #include <arduino.h>
#endif



c_i2c::c_i2c()
{
    
}


void c_i2c::init(void)
{
#if USE_ARDUINO
    Wire.begin();
    Wire.setClock(400000u);
#else
    //set SCL to 400kHz
    TWSR = 0x00;
    TWBR = 0x0C;
    //enable TWI
    TWCR = (1<<TWEN);
#endif
}


void c_i2c::transfer_begin(uint8_t slave_address)
{
#if USE_ARDUINO
    Wire.beginTransmission(slave_address);
#else
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    while ((TWCR & (1<<TWINT)) == 0)
    {
        // Wait for the interface.
    }
#endif
}


void c_i2c::send_byte(uint8_t byte)
{
#if USE_ARDUINO
    Wire.write(byte);
#else
    TWDR = byte;
    TWCR = (1<<TWINT)|(1<<TWEN);
    while ((TWCR & (1<<TWINT)) == 0)
    {
        // Wait for the byte to be sent.
    }
#endif
}


uint8_t c_i2c::receive_byte(i2c_receive_response_t send_ack)
{
#if USE_ARDUINO

#else
    TWCR = (1u << TWINT)|(1u << TWEN);

    if (ACK == send_ack)
    {
        TWCR |= (1u << TWEA);
    }

    while ((TWCR & (1u << TWINT)) == 0)
    {
        // Wait for the byte.
    }
    return TWDR;
#endif
}


void c_i2c::transfer_end(void)
{
#if USE_ARDUINO
    Wire.endTransmission();
#else
    TWCR = (1u << TWINT)|(1u << TWSTO)|(1u << TWEN);
#endif
}


uint8_t c_i2c::status(void)
{
    return (uint8_t)(TWSR & 0xF8);
}
