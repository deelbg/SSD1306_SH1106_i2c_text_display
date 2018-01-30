#include <stdint.h>
#include "hal_text_display.h"


c_text_display::c_text_display(uint8_t i2c_address) :
                               address(i2c_address), 
                               r_display(Adafruit_SSD1306(4))
{
    
}


void c_text_display::init(void)
{
    r_display.begin(SSD1306_SWITCHCAPVCC, address);
    r_display.clearDisplay();
    r_display.setTextColor(WHITE, BLACK);
    r_display.setCursor(0,0);
    r_display.display();    
}


void c_text_display::clear(void)
{
    r_display.clearDisplay();    
    r_display.setTextSize(font_size);
    r_display.setTextColor(WHITE, BLACK);
}



void c_text_display::dim(bool dim)
{
    r_display.dim(dim);
}


void c_text_display::show(void)
{
    r_display.display();
}


void c_text_display::print(char * p_str)
{
    r_display.print(p_str);
}


void c_text_display::println(char * p_str)
{
    r_display.println(p_str);
}


void c_text_display::set_font_size(uint8_t size)
{
    font_size = ( 3u >= size) ? size : 3u;
    r_display.setTextSize(font_size);
}


void c_text_display::set_possition(uint8_t position_x, uint8_t position_y)
{
    r_display.setCursor((position_x * 12u), (position_y * 16u));
}


void c_text_display::set_cursor(uint8_t position_x, uint8_t position_y)
{
    for (uint8_t index = 0; index < 3; index++)
    {
        r_display.drawLine((position_x * 12), ((position_y * 16) + (16 - index)), 
                           ((position_x * 12) + 10), ((position_y * 16) + (16 - index)), WHITE);
    }
}
