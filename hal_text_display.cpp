#include <stdint.h>
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "hal_text_display.h"


c_text_display::c_text_display(Adafruit_SSD1306 & ref_display, uint8_t i2c_address, uint8_t font):
                               r_display(ref_display), address(i2c_address), 
                               font_size(font)
{
    init();  
}


void c_text_display::init(void)
{
    r_display.begin(SSD1306_SWITCHCAPVCC, address);
    r_display.clearDisplay();
    r_display.setTextSize(font_size);
    r_display.setTextColor(WHITE, BLACK);
    r_display.setCursor(0,0);
    r_display.display();    
}


void c_text_display::clear(void)
{
    // r_display.clearDisplay();    
//     r_display.setTextSize(font_size);
//     r_display.setTextColor(WHITE, BLACK);


    char buff[11] = {};

    r_display.clearDisplay();
    r_display.setTextSize(2);
    r_display.setTextColor(WHITE, BLACK);
    r_display.setCursor(0,0);
    
    
    sprintf(buff, "test %d", 1); 
    r_display.println(buff);

    // set_cursor(0, 2);
    
    r_display.display();
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
    font_size = size;
    r_display.setTextSize(font_size);
}


void c_text_display::set_possition(uint8_t position_x, uint8_t position_y)
{
    // r_display.setCursor((position_x * 10u), (position_y * 16u));
    r_display.setCursor(position_x, position_y);
}


void c_text_display::set_cursor(uint8_t position_x, uint8_t position_y)
{
    r_display.drawLine((position_x * 12), (position_y * 16), 
                     (position_x * 12 + 9), ((position_y) * 16), WHITE);
}
