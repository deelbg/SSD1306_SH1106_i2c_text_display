#include <stdint.h>
#include "hal_i2c.h"
#include "hal_text_display.h"

static const uint8_t OLED_ADDRESS = 0x3Cu;

c_i2c g_i2c = c_i2c();
c_text_display g_display = c_text_display(g_i2c, OLED_ADDRESS);



void setup()
{
    Serial.begin(115200);
    g_i2c.init();
    g_display.init(c_text_display::SSD1306_VCC_SWITCHCAP);
    g_display.clear();
    g_display.dim(true);
}


void loop()
{
    g_display.clear();
    g_display.set_font_size(0);
    g_display.println("012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567");
    delay(1000);

    g_display.clear();
    g_display.set_font_size(1);
    g_display.println("0123456789012345678901234567890123456789");
    delay(1000);
    
    g_display.clear();
    g_display.set_font_size(2);
    g_display.println("0123456789");
    delay(1000);
}
