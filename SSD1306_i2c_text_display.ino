#include <stdint.h>
#include "hal_i2c_twi.h"
#include "SSD1306_i2c_text_display.h"

static const uint32_t CPU_FREQUENCY = 16000000u;
static const uint32_t I2C_FREQUENCY = 400000u;
static const uint8_t  OLED_ADDRESS = 0x3Cu;

c_i2c g_i2c = c_i2c();
c_text_display g_display = c_text_display(g_i2c, OLED_ADDRESS);



void setup()
{
    // Serial.begin(115200);
    g_i2c.init(CPU_FREQUENCY, I2C_FREQUENCY);
    g_display.init(c_text_display::VCC_SWITCHCAP);
    g_display.clear();
    g_display.dim(true);
}


void loop()
{
    char ch = 0x20;

    g_display.clear();
    
    for (uint8_t font_size = 0; font_size <= 2; font_size++ )
    {
        ch = 0x20;
        g_display.set_font_size(font_size);
        g_display.set_cursor(0, 0);

        do
        {
            g_display.print_char(ch);
            delay(200);
        }
        while(ch < 0xFF);


        delay(2000);
    } 
}
