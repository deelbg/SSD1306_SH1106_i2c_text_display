#ifndef TEXT_DISPLAY_H
#define TEXT_DISPLAY_H

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


class c_text_display
{
    public:
        c_text_display(uint8_t i2c_address);

        void init(void);
        void clear(void);
        void dim(bool dim);
        void show(void);
        void print(char * p_str);
        void println(char * p_str);
        void set_font_size(uint8_t size);
        void set_possition(uint8_t position_x, uint8_t position_y);
        void set_cursor(uint8_t position_x, uint8_t position_y);
                
    private:
        uint8_t address;
        uint8_t font_size;

        Adafruit_SSD1306 r_display;
};

#endif //TEXT_DISPLAY_H
