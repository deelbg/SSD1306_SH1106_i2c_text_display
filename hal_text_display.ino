#include <stdint.h>
#include "hal_i2c_twi.h"
#include "hal_text_display.h"

static const uint32_t CPU_FREQUENCY = 16000000u;
static const uint32_t I2C_FREQUENCY = 400000u;
static const uint8_t OLED_ADDRESS = 0x3Cu;

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
    g_display.clear();
    g_display.set_font_size(0);
    g_display.show_cursor(2, 5);
    // g_display.println("012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567");
    // g_display.hide_cursor();
    // delay(1000);

    // g_display.clear();
    // g_display.set_font_size(1);
    // g_display.show_cursor(2, 2);
    // g_display.println("0123456789012345678901234567890123456789");
    // g_display.hide_cursor();
    // delay(1000);
    
    // g_display.clear();
    // g_display.set_font_size(2);
    // g_display.show_cursor(3, 1);
    // g_display.println("0123456789");
    // delay(2000);
    
    // g_display.hide_cursor();
    g_display.set_cursor(3, 1);
    g_display.println('8910');
    g_display.hide_cursor();

    while(1){}
}
