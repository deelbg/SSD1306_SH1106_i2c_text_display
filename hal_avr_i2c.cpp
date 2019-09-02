#include <stdint.h>
#include <avr/io.h>
#include <util/twi.h>
#include "hal_avr_i2c.h"

#ifdef I2C_FAST_MODE_400KHZ
#define F_I2C 400000ul
#else
#define F_I2C 100000ul
#endif 

#ifdef I2C_HARDWARE_USI
// USI hardware
#include <util/delay.h>

// These delays guarantee only that the speed is not higher than the desired one, 
// but not that it will be axactly equal to it.
// Half period time in nS for given i2c speed in Hz.
// Calculate the delay for a halfperiod in uS/10.
// delay = ((1000000000ul / i2c_speed_hz) / 2u ) - 1000ul;
// reduce the delay with 1uS to account for the switching and processing time.
// +-----------------------------+
// | i2c_speed (Hz) | delay (nS) |
// +-----------------------------+
// | 100 000        | 4000       |
// | 400 000        | 250        |
// +-----------------------------+
#ifdef I2C_FAST_MODE_400KHZ
#define I2C_DELAY()           (_delay_us(0.1))
#else
#define I2C_DELAY()           (_delay_us(4))
#endif

#define USI_SCL_SET_INPUT()   (USI_DDR  &= ~(1u << USI_SCL_DDA))
#define USI_SCL_SET_OUTPUT()  (USI_DDR  |=  (1u << USI_SCL_DDA))

#define USI_SDA_SET_INPUT()   (USI_DDR  &= ~(1u << USI_SDA_DDA))
#define USI_SDA_SET_OUTPUT()  (USI_DDR  |=  (1u << USI_SDA_DDA))

#define USI_SCL_SET_HIGH()    (USI_PORT |=  (1u << USI_SCL_PORT_PIN))
#define USI_SCL_SET_LOW()     (USI_PORT &= ~(1u << USI_SCL_PORT_PIN))

#define USI_SDA_SET_HIGH()    (USI_PORT |=  (1u << USI_SDA_PORT_PIN))
#define USI_SDA_SET_LOW()     (USI_PORT &= ~(1u << USI_SDA_PORT_PIN))

#define USI_SCL_GET()         (USI_PIN & (1u << USI_SCL_PIN))
#define USI_SDA_GET()         (USI_PIN & (1u << USI_SDA_PIN))

#define USI_SCL_WAIT_HIGH()   {while (0x00u == USI_SCL_GET()){}}

#endif // I2C_HARDWARE_USI


c_i2c::c_i2c()
{
#ifdef I2C_HARDWARE_USI
// USI hardware
#else // I2C_HARDWARE_USI
// TWI hardware

    init();

#endif // I2C_HARDWARE_USI
}


void c_i2c::init(void)
{
#ifdef I2C_HARDWARE_USI
// USI hardware
#else // I2C_HARDWARE_USI
// TWI hardware

    // Prescaler is not used. 
    TWSR = 0x00u;
    TWBR = ((F_CPU / F_I2C) - 16u) / 2u;
    //enable TWI
    TWCR = (1u << TWINT) | (1u << TWEN);

#endif // I2C_HARDWARE_USI
}

bool c_i2c::start_write(uint8_t slave_address)
{
#ifdef I2C_HARDWARE_USI
// USI hardware

    send_start();

    return write_byte(slave_address << 1u);

#else // I2C_HARDWARE_USI
// TWI hardware

    transfer_begin();
    write_byte(slave_address << 1u);

    return (c_i2c::I2C_WRITE_ADDRESS_ACK == status()) ? true : false;

#endif // I2C_HARDWARE_USI
}


bool c_i2c::start_read(uint8_t slave_address)
{
#ifdef I2C_HARDWARE_USI
// USI hardware

    send_start();

    return write_byte((slave_address << 1u) | 0x01u );

#else // I2C_HARDWARE_USI
// TWI hardware

    transfer_begin();
    write_byte((slave_address << 1u) | 0x01);

    return (c_i2c::I2C_READ_ADDRESS_ACK == status()) ? true : false;

#endif // I2C_HARDWARE_USI
}


void c_i2c::stop(void)
{
#ifdef I2C_HARDWARE_USI
// USI hardware

    // Generate i2c stop condition, switch data to high while clock is high.
    // By switching them to inputs they go high, also safer when no transfer.
    USI_SDA_SET_LOW();
    I2C_DELAY();
    USI_SCL_SET_INPUT();
    USI_SDA_SET_INPUT();    
    USICR = 0x00u;

#else // I2C_HARDWARE_USI
// TWI hardware

    TWCR = (1u << TWINT) | (1u << TWSTO) | (1u << TWEN);

#endif // I2C_HARDWARE_USI
}


bool c_i2c::write_byte(uint8_t byte)
{
#ifdef I2C_HARDWARE_USI
// USI hardware

    uint8_t result = 0x00;

    // Send 8 bits.
    usi_transfer(byte, 8u);

    // Read 1 bit - ACK/NACK
    USI_SDA_SET_INPUT();

    result = usi_transfer(0x00u, 1u);

    USI_SDA_SET_OUTPUT();

    return (bool)(result & 0x01u);

#else // I2C_HARDWARE_USI
// TWI hardware

    TWDR = byte;
    TWCR = (1u << TWINT) | (1u << TWEN);

    while (0x00u == (TWCR & (1u << TWINT)))
    {

    }

    return (c_i2c::I2C_WRITE_DATA_ACK == status()) ? true: false;

#endif // I2C_HARDWARE_USI
}


uint8_t c_i2c::read_byte(c_i2c::i2c_receive_response_t send_ack)
{
#ifdef I2C_HARDWARE_USI

    uint8_t result = 0x00;

    // Read 8 bits.    
    USI_SDA_SET_INPUT();

    result = usi_transfer(0x00, 8u);

    USI_SDA_SET_OUTPUT();

    // Send 1 bit - ACK/NACK
    usi_transfer(((ACK == send_ack) ? 0x00u : 0xFFu), 1u); 

    return result;

#else // I2C_HARDWARE_USI
// TWI hardware

    if (ACK == send_ack)
    {
        TWCR |= (1 << TWEA);
    }
    else
    {
        TWCR &= ~(1 << TWEA);
    }

    TWCR |= (1u << TWINT) | (1u << TWEN);
    
    while (0x00u == (TWCR & (1<<TWINT)))
    {

    }

    return TWDR;

#endif // I2C_HARDWARE_USI
}


uint8_t c_i2c::status(void)
{
#ifdef I2C_HARDWARE_USI

    return 0x00;

#else // I2C_HARDWARE_USI

    return (uint8_t)(TWSR & 0xF8);
    
#endif // I2C_HARDWARE_USI
}


#ifdef I2C_HARDWARE_USI
// USI hardware
void c_i2c::send_start(void)
{
    //  Generate i2c start condition, switch data to low while clock is high  
    USICR = 0x00u;
    USI_SCL_SET_OUTPUT();
    USI_SDA_SET_OUTPUT();

    USI_SDA_SET_HIGH();
    USI_SCL_SET_HIGH();

    USI_SDA_SET_LOW();
    USI_SCL_SET_LOW();

    USIDR = 0x00u;
    USICR = (1u << USIWM1);
    USI_SDA_SET_HIGH();
}


uint8_t c_i2c::usi_transfer(uint8_t data_to_send, uint8_t bit_number)
{    
    uint8_t result = 0u;
    USIDR = data_to_send;

    // Send "bit_number" bits in software usi clock mode.
    if ((bit_number > 0u) && (bit_number <= 8u))
    {
        USISR = 0xFFu - (bit_number - 1);

        while (!(USISR & (1u << USIOIF)))
        {   
            I2C_DELAY();
            USICR = (1u << USIWM1) | (1u << USITC);                    
            USI_SCL_WAIT_HIGH();
            I2C_DELAY();
            USICR = (1u << USIWM1) | (1u << USICLK) | (1u << USITC);
        }

        result = USIDR;
    }

    return result;
}

#else // I2C_HARDWARE_USI
// TWI hardware
void c_i2c::transfer_begin(void)
{
    TWCR = (1u << TWINT) | (1u << TWSTA) | (1u << TWEN);

    while (0x00u == (TWCR & (1 << TWINT)))
    {

    }
}

#endif // I2C_HARDWARE_USI
