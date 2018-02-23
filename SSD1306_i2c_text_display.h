#ifndef TEXT_DISPLAY_H
#define TEXT_DISPLAY_H

#include "hal_i2c_twi.h"

#define TEXT_DISPLAY_VERSION_MAJOR 1
#define TEXT_DISPLAY_VERSION_MINOR 1

class c_text_display
{
    public:
        enum vcc_source_t
        {
            VCC_EXTERNAL,
            VCC_SWITCHCAP
        };

        c_text_display(c_i2c & ref_i2c, uint8_t i2c_address);

        void init(vcc_source_t vcc);
        void clear(void);
        void dim(bool dim);
        void show(void);
        void print_char(char ch);        
        void print_number(uint16_t number, uint8_t width);
        void print(char * p_str);
        void println(char * p_str);
        void set_font_size(uint8_t size);
        void set_cursor(uint8_t position_x, uint8_t position_y);
        void show_cursor(uint8_t position_x, uint8_t position_y);
        void hide_cursor(void);
                
    private:

        static const uint8_t  LCD_WIDTH       = 128u;
        static const uint8_t  LCD_HEIGHT      = 64u;
        static const uint16_t LCD_BUFFER_SIZE = (uint16_t)LCD_WIDTH * 
                                                          (uint16_t)(LCD_HEIGHT / 8u);

        static const uint8_t  COMMAND                   = 0x00u;
        static const uint8_t  DATA                      = 0x40u;

        static const uint8_t CMD_SETCONTRAST            = 0x81u;
        static const uint8_t CMD_DISPLAYALLON_RESUME    = 0xA4u;
        static const uint8_t CMD_DISPLAYALLON           = 0xA5u;
        static const uint8_t CMD_NORMALDISPLAY          = 0xA6u;
        static const uint8_t CMD_INVERTDISPLAY          = 0xA7u;
        static const uint8_t CMD_DISPLAYOFF             = 0xAEu;
        static const uint8_t CMD_DISPLAYON              = 0xAFu;
        static const uint8_t CMD_SETDISPLAYOFFSET       = 0xD3u;
        static const uint8_t CMD_SETCOMPINS             = 0xDAu;
        static const uint8_t CMD_SETVCOMDETECT          = 0xDBu;
        static const uint8_t CMD_SETDISPLAYCLOCKDIV     = 0xD5u;
        static const uint8_t CMD_SETPRECHARGE           = 0xD9u;
        static const uint8_t CMD_SETMULTIPLEX           = 0xA8u;
        static const uint8_t CMD_SETLOWCOLUMN           = 0x00u;
        static const uint8_t CMD_SETHIGHCOLUMN          = 0x10u;
        static const uint8_t CMD_SETSTARTLINE           = 0x40u;
        static const uint8_t CMD_MEMORYMODE             = 0x20u;
        static const uint8_t CMD_COLUMNADDR             = 0x21u;
        static const uint8_t CMD_PAGEADDR               = 0x22u;
        static const uint8_t CMD_COMSCANINC             = 0xC0u;
        static const uint8_t CMD_COMSCANDEC             = 0xC8u;
        static const uint8_t CMD_SEGREMAP               = 0xA0u;
        static const uint8_t CMD_CHARGEPUMP             = 0x8Du;
        static const uint8_t CMD_ACTIVATE_SCROLL            = 0x2F;
        static const uint8_t CMD_DEACTIVATE_SCROLL          = 0x2E;
        static const uint8_t CMD_SET_VERTICAL_SCROLL_AREA   = 0xA3;
        static const uint8_t CMD_RIGHT_HORIZONTAL_SCROLL    = 0x26;
        static const uint8_t CMD_LEFT_HORIZONTAL_SCROLL     = 0x27;
        static const uint8_t CMD_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL = 0x29;
        static const uint8_t CMD_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL  = 0x2A;

        uint8_t address;
        uint8_t dot_size;        
        uint8_t current_x;
        uint8_t current_y;
        uint8_t cursor_x;
        uint8_t cursor_y;
        bool    cursor_on;
        vcc_source_t vcc_source;
        c_i2c & r_i2c;


        void send_command(uint8_t command);        
        void set_possition(uint8_t position_x, uint8_t position_y);
};

#endif //TEXT_DISPLAY_H
