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
    g_display.clear();
    g_display.dim(true);

    g_display.set_font_size(1);
    g_display.println("0123456789");
    g_display.print("01234567890123");    
    g_display.set_font_size(0);    
    g_display.set_cursor(8u, 5u);
    g_display.println("01234567890123456789");
}


void loop()
{
    // for (uint8_t index = 0; index < 92; index++)
    // {
        
    //     g_display.set_font_size(0);
    //     g_display.print_char('B');
    //     delay(2000);
    //     g_display.set_font_size(1);
    //     g_display.print_char('B');
    //     delay(2000);
    //     g_display.set_font_size(2);
    //     g_display.print_char('B');
    //     delay(2000);
    // // }
}
