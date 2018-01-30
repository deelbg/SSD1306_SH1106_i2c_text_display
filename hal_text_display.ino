#include "hal_text_display.h"

c_text_display g_display = c_text_display(0x3Cu);


void setup()
{
    g_display.init();
    g_display.dim(true);
}



void loop()
{
    static uint8_t counter = 0u;
    static uint8_t x = 0u;
    static uint8_t y = 0u;
    static char str_buff[11] = {};


    g_display.clear(); 
    g_display.set_possition(0, 0);
    g_display.set_font_size(2);

    sprintf(str_buff, "0123456789");
    g_display.println(str_buff);
    g_display.println(str_buff);
    g_display.println(str_buff);
    g_display.println(str_buff);

    g_display.show();

    g_display.set_possition(x, y);

    sprintf(str_buff, "%d", x);
    g_display.println(str_buff);

    g_display.set_cursor(x, y);

    g_display.show();

    x = (x < 9) ? x + 1 : 0;
    
    if (0 == x)
    {
        y = (y < 3) ? y + 1 : 0;
    }

    counter++;

    delay(1000);

    if (40 == counter)
    {
        counter = 0;

        g_display.dim(false);

        delay(5000);

        g_display.dim(true);
    }
}
