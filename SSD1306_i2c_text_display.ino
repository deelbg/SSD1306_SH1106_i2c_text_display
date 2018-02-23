#include <stdint.h>
#include "hal_i2c_twi.h"
#include "SSD1306_i2c_text_display.h"

static const uint32_t CPU_FREQUENCY = 16000000u;
static const uint32_t I2C_FREQUENCY = 400000u;
static const uint8_t  OLED_ADDRESS = 0x3Cu;

c_i2c g_i2c = c_i2c();
c_text_display g_display = c_text_display(g_i2c, OLED_ADDRESS);

char str_buff[200] = {};

void setup()
{
    g_i2c.init(CPU_FREQUENCY, I2C_FREQUENCY);
    g_display.init(c_text_display::VCC_SWITCHCAP);
    g_display.clear();
    g_display.dim(true);

    uint8_t pos = 0;
    char ch = 0x20;

    for (uint8_t pos = 0; pos < 156; pos++ )
    {
        str_buff[pos] = ch;
        
        if (0x7A == ch)
        {
            ch = 0xC0;
        }
        else
        {
            ch++;
        }
    }

    str_buff[156] = '\0';
}


void loop()
{
   

    g_display.clear();
    g_display.set_font_size(0);
    g_display.print(str_buff);
    delay(5000);

    g_display.clear();
    g_display.set_font_size(1);
    g_display.print(str_buff);
    delay(5000);

    // TODO example for positioning, font size, cursor. 
}
