// ==============================================================================
// MIT License

// Copyright (c) 2019 Deyan Todorov

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// ==============================================================================


#ifndef I2C_H
#define I2C_H

#define I2C_VERSION_MAJOR 1
#define I2C_VERSION_MINOR 0
#define I2C_VERSION_PATCH 0

// NOTE: Adjust the CPU frequency.
#define F_CPU 16000000ul
// Uncommment for 400kHz. Leve commented out for 100kHz.
#define I2C_FAST_MODE_400KHZ
// Uncommment for USI hardware. Leve commented out for TWI.
// #define I2C_HARDWARE_USI

#ifdef I2C_HARDWARE_USI
#define I2C_PINS
#define USI_DDR               DDRB
#define USI_SCL_DDA           DDB2
#define USI_SDA_DDA           DDB0

#define USI_PORT              PORTB
#define USI_SCL_PORT_PIN      PORTB2
#define USI_SDA_PORT_PIN      PORTB0

#define USI_PIN               PINB
#define USI_SCL_PIN           PINB2
#define USI_SDA_PIN           PINB0
#endif // I2C_HARDWARE_USI

class c_i2c
{
    public:
        enum i2c_receive_response_t
        {
            ACK,
            NACK
        };

        enum i2c_status_t
        {
            I2C_START_OK            = 0x08,
            I2C_START_REPEATED      = 0x10,
            I2C_WRITE_ADDRESS_ACK   = 0x18,
            I2C_WRITE_ADDRESS_NACK  = 0x20,
            I2C_WRITE_DATA_ACK      = 0x28,
            I2C_WRITE_DATA_NACK     = 0x30,
            I2C_ARBITRATION_LOST    = 0x38,
            I2C_READ_ADDRESS_ACK    = 0x40,
            I2C_READ_ADDRESS_NACK   = 0x48,  
            I2C_READ_DATA_ACK       = 0x50,  
            I2C_READ_DATA_NACK      = 0x58 
        };

        c_i2c();
        bool start_write(uint8_t slave_address);
        bool start_read(uint8_t slave_address);
        void stop(void);
        bool write_byte(uint8_t byte);
        uint8_t read_byte(i2c_receive_response_t send_ack); 
        uint8_t status(void);
                
        void init(void);
    private:

#ifdef I2C_HARDWARE_USI
        void send_start(void);
        uint8_t usi_transfer(uint8_t data_to_send, uint8_t bit_number);
#else // I2C_HARDWARE_USI
        void transfer_begin(void);
#endif // I2C_HARDWARE_USI

};

#endif //I2C_H
