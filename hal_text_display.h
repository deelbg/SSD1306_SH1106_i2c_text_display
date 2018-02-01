#ifndef TEXT_DISPLAY_H
#define TEXT_DISPLAY_H

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "hal_i2c.h"

class c_text_display
{
    public:
        enum vcc_source_t
        {
            SSD1306_VCC_EXTERNAL,
            SSD1306_VCC_SWITCHCAP
        };

        c_text_display(c_i2c & ref_i2c, uint8_t i2c_address);

        void init(vcc_source_t vcc_source);
        void clear(void);
        void dim(bool dim);
        void show(void);
        void print(char * p_str);
        void println(char * p_str);
        void set_font_size(uint8_t size);
        void set_possition(uint8_t position_x, uint8_t position_y);
        void set_cursor(uint8_t position_x, uint8_t position_y);
                
    private:

        static const uint8_t SSD1306_CMD_LCDWIDTH               = 128u;
        static const uint8_t SSD1306_CMD_LCDHEIGHT              = 64u;
        static const uint8_t SSD1306_CMD_SETCONTRAST            = 0x81u;
        static const uint8_t SSD1306_CMD_DISPLAYALLON_RESUME    = 0xA4u;
        static const uint8_t SSD1306_CMD_DISPLAYALLON           = 0xA5u;
        static const uint8_t SSD1306_CMD_NORMALDISPLAY          = 0xA6u;
        static const uint8_t SSD1306_CMD_INVERTDISPLAY          = 0xA7u;
        static const uint8_t SSD1306_CMD_DISPLAYOFF             = 0xAEu;
        static const uint8_t SSD1306_CMD_DISPLAYON              = 0xAFu;
        static const uint8_t SSD1306_CMD_SETDISPLAYOFFSET       = 0xD3u;
        static const uint8_t SSD1306_CMD_SETCOMPINS             = 0xDAu;
        static const uint8_t SSD1306_CMD_SETVCOMDETECT          = 0xDBu;
        static const uint8_t SSD1306_CMD_SETDISPLAYCLOCKDIV     = 0xD5u;
        static const uint8_t SSD1306_CMD_SETPRECHARGE           = 0xD9u;
        static const uint8_t SSD1306_CMD_SETMULTIPLEX           = 0xA8u;
        static const uint8_t SSD1306_CMD_SETLOWCOLUMN           = 0x00u;
        static const uint8_t SSD1306_CMD_SETHIGHCOLUMN          = 0x10u;
        static const uint8_t SSD1306_CMD_SETSTARTLINE           = 0x40u;
        static const uint8_t SSD1306_CMD_MEMORYMODE             = 0x20u;
        static const uint8_t SSD1306_CMD_COLUMNADDR             = 0x21u;
        static const uint8_t SSD1306_CMD_PAGEADDR               = 0x22u;
        static const uint8_t SSD1306_CMD_COMSCANINC             = 0xC0u;
        static const uint8_t SSD1306_CMD_COMSCANDEC             = 0xC8u;
        static const uint8_t SSD1306_CMD_SEGREMAP               = 0xA0u;
        static const uint8_t SSD1306_CMD_CHARGEPUMP             = 0x8Du;
        static const uint8_t SSD1306_CMD_ACTIVATE_SCROLL            = 0x2F;
        static const uint8_t SSD1306_CMD_DEACTIVATE_SCROLL          = 0x2E;
        static const uint8_t SSD1306_CMD_SET_VERTICAL_SCROLL_AREA   = 0xA3;
        static const uint8_t SSD1306_CMD_RIGHT_HORIZONTAL_SCROLL    = 0x26;
        static const uint8_t SSD1306_CMD_LEFT_HORIZONTAL_SCROLL     = 0x27;
        static const uint8_t SSD1306_CMD_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL = 0x29;
        static const uint8_t SSD1306_CMD_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL  = 0x2A;

        uint8_t address;
        uint8_t font_size;
        c_i2c & r_i2c;

        Adafruit_SSD1306 display = Adafruit_SSD1306(4);

        void send_command(uint8_t command);
        void send_data_start(void);
        void send_data_byte(uint8_t byte);
        void send_data_end(void);
};

#endif //TEXT_DISPLAY_H
