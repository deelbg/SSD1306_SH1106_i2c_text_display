#include <stdint.h>
#include "hal_i2c.h"
#include "hal_text_display.h"

static const uint8_t OLED_ADDRESS = 0x3Cu;

c_i2c g_i2c = c_i2c();
c_text_display g_display = c_text_display(g_i2c, OLED_ADDRESS);



void setup()
{
    g_i2c.init();
    g_display.init(c_text_display::SSD1306_VCC_SWITCHCAP);
}


void loop()
{
    g_display.show();

    delay(500);

    g_display.dim(true);

    delay(500);

    g_display.dim(false);

    delay(500);

    g_display.clear();

    for (uint8_t index = 0; index < 92; index++)
    {
        g_display.print_char(' ' + index);
        delay(200);
    }
}
