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
    static uint8_t counter = 0u;

    if (35u == counter)
    {
        counter = 0u;

        g_display.show();

        delay(1000);

        g_display.dim(true);

        delay(1000);

        g_display.dim(false);

        delay(1000);

        g_display.clear();
    }

    g_display.send_byte(0x00u);
    g_display.send_byte(0x00u);
    g_display.send_byte(0x00u);
    g_display.send_byte(0x00u);
    g_display.send_byte(0x00u);
    g_display.send_byte(0x00u);
    g_display.send_byte(0x00u);
    g_display.send_byte(0x00u);
    g_display.send_byte(0x00u);
    g_display.send_byte(0x00u);
    g_display.send_byte(0x00u);
    g_display.send_byte(0x00u);
    g_display.send_byte(0x00u);
    g_display.send_byte(0x00u);

    g_display.send_byte(0x0Fu);
    g_display.send_byte(0x00u);
    g_display.send_byte(0xF0u);
    g_display.send_byte(0x00u);
    g_display.send_byte(0x01u);
    g_display.send_byte(0x02u);
    g_display.send_byte(0x04u);
    g_display.send_byte(0x08u);
    g_display.send_byte(0x10u);
    g_display.send_byte(0x10u);
    g_display.send_byte(0x20u);
    g_display.send_byte(0x40u);
    g_display.send_byte(0x80u);
    g_display.send_byte(0xFFu);
    delay(50);

    counter++;
}


// void loop()
// {    
//     static uint8_t counter = 0u;
//     static uint8_t x = 0u;
//     static uint8_t y = 0u;
//     static char str_buff[11] = {};

//     g_display.clear(); 
//     g_display.set_possition(0, 0);
//     g_display.set_font_size(2);

//     sprintf(str_buff, "0123456789");
//     g_display.println(str_buff);
//     g_display.println(str_buff);
//     g_display.println(str_buff);
//     g_display.println(str_buff);

//     g_display.show();

//     g_display.set_possition(x, y);

//     sprintf(str_buff, "%d", x);
//     g_display.println(str_buff);

//     g_display.set_cursor(x, y);

//     g_display.show();

//     x = (x < 9) ? x + 1 : 0;
    
//     if (0 == x)
//     {
//         y = (y < 3) ? y + 1 : 0;
//     }

//     counter++;

//     delay(1000);

//     if (40 == counter)
//     {
//         counter = 0;

//         g_display.dim(false);

//         delay(5000);

//         g_display.dim(true);
//     }
// }
