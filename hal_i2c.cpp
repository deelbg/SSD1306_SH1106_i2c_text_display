#include "hal_i2c.h"

c_i2c::c_i2c()
{
    
}


void c_i2c::init(void)
{
    Wire.begin();
}


void c_i2c::transfer_begin(uint8_t slave_address)
{
    Wire.beginTransmission(slave_address);
}


void c_i2c::transfer_byte(uint8_t byte)
{
    Wire.write(byte);
}


void c_i2c::transfer_end(void)
{
    Wire.endTransmission();
}
