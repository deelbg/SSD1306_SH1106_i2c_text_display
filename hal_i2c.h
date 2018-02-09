#ifndef I2C_H
#define I2C_H


class c_i2c
{
    public:
        enum i2c_receive_response_t
        {
            ACK,
            NACK
        };

        c_i2c();
        void init(void);
        void transfer_begin(uint8_t slave_address);
        void transfer_end(void);
        void send_byte(uint8_t byte);
        uint8_t receive_byte(i2c_receive_response_t send_ack);        
        uint8_t status(void);
                
    private:
        enum i2c_status_t
        {

        };

};

#endif //I2C_H
