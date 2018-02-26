#ifndef I2C_TWI_H
#define I2C_TWI_H

#define I2C_TWI_VERSION_MAJOR 1
#define I2C_TWI_VERSION_MINOR 0


class c_i2c
{
    public:
        enum i2c_receive_response_t
        {
            ACK,
            NACK
        };

        c_i2c();
        void init(uint32_t f_cpu, uint32_t f_i2c = 100000u);
        void transfer_begin(uint8_t slave_address);
        void transfer_end(void);
        void send_byte(uint8_t byte);
        uint8_t receive_byte(i2c_receive_response_t send_ack);        
        uint8_t status(void);
                
    private:

};

#endif //I2C_H
