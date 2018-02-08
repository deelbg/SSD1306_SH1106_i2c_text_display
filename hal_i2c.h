#ifndef I2C_H
#define I2C_H


class c_i2c
{
    public:
        c_i2c();
        void init(void);
        void transfer_begin(uint8_t slave_address);
        void transfer_byte(uint8_t byte);
        void transfer_end(void);
                
    private:

};

#endif //I2C_H
