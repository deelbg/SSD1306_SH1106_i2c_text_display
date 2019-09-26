// ==============================================================================
// MIT License

// Copyright (c) 2019 Deyan Todorov

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// ==============================================================================


#ifndef SSD1306_SH1106_TEXT_DISPLAY_H
#define SSD1306_SH1106_TEXT_DISPLAY_H

#include "hal_avr_i2c.h"
#include "font_h5_v8.h"

#define TEXT_DISPLAY_VERSION_MAJOR 1
#define TEXT_DISPLAY_VERSION_MINOR 0
#define TEXT_DISPLAY_VERSION_PATCH 0


class c_SSD1306_SH1106_i2c
{
    public:
        enum vcc_source_t
        {
            VCC_EXTERNAL,
            VCC_SWITCHCAP
        };

        c_SSD1306_SH1106_i2c(c_i2c & ref_i2c, uint8_t i2c_address);

        void init(vcc_source_t vcc);
        void set_offset_x(uint8_t offset);
        void set_contrast(uint8_t contrast, uint8_t contrast_dim);
        void clear(void);
        void power_on(bool power);
        void dim(bool dim);
        void print_char(char ch);
        void print_number(uint16_t number, uint8_t width);
        void print(char * p_str);
        void println(char * p_str);
        void set_font_size(uint8_t size);
        void set_possition(uint8_t position_x, uint8_t position_y);
        void show_cursor(uint8_t position_x, uint8_t position_y);
        void hide_cursor(void);
            
    protected:

        void send_command(uint8_t command);
        void send_data(uint8_t data_byte);
        void set_possition_raw(uint8_t position_x, uint8_t position_y);

    private: 

        static const uint8_t  LCD_WIDTH                 = 128u;
        static const uint8_t  LCD_HEIGHT                = 64u;

        static const uint8_t  COMMAND                   = 0x00u;
        static const uint8_t  DATA                      = 0x40u;

        static const uint8_t CMD_SET_CONTRAST           = 0x81u;
        static const uint8_t CMD_DISPLAY_ALL_ON_RESUME  = 0xA4u;
        static const uint8_t CMD_DISPLAY_ALL_ON         = 0xA5u;
        static const uint8_t CMD_NORMAL_DISPLAY         = 0xA6u;
        static const uint8_t CMD_INVERT_DISPLAY         = 0xA7u;
        static const uint8_t CMD_DISPLAY_OFF            = 0xAEu;
        static const uint8_t CMD_DISPLAY_ON             = 0xAFu;
        static const uint8_t CMD_SET_PAGE_START_ADDRESS = 0xB0u;
        static const uint8_t CMD_SET_DISPLAY_OFFSET     = 0xD3u;
        static const uint8_t CMD_SET_COM_PINS           = 0xDAu;
        static const uint8_t CMD_SET_V_COM_DETECT       = 0xDBu;
        static const uint8_t CMD_SET_DISPLAY_CLOCK_DIV  = 0xD5u;
        static const uint8_t CMD_SET_PRECHARGE          = 0xD9u;
        static const uint8_t CMD_SET_MULTIPLEX          = 0xA8u;
        static const uint8_t CMD_SET_COLUMN_NUMBER_LOW  = 0x00u;
        static const uint8_t CMD_SET_COLUMN_NUMBER_HIGH = 0x10u;
        static const uint8_t CMD_SET_START_LINE_NUMBER  = 0x40u;
        static const uint8_t CMD_MEMORY_MODE            = 0x20u;
        static const uint8_t CMD_SET_COLUMN_ADDRESS     = 0x21u;
        static const uint8_t CMD_SET_PAGE_ADDRESS       = 0x22u;
        static const uint8_t CMD_COM_SCAN_INC           = 0xC0u;
        static const uint8_t CMD_COM_SCAN_DEC           = 0xC8u;
        static const uint8_t CMD_SEGMENT_REMAP          = 0xA0u;
        static const uint8_t CMD_CHARGE_PUMP            = 0x8Du;
        static const uint8_t CMD_ACTIVATE_SCROLL            = 0x2F;
        static const uint8_t CMD_DEACTIVATE_SCROLL          = 0x2E;
        static const uint8_t CMD_SET_VERTICAL_SCROLL_AREA   = 0xA3;
        static const uint8_t CMD_RIGHT_HORIZONTAL_SCROLL    = 0x26;
        static const uint8_t CMD_LEFT_HORIZONTAL_SCROLL     = 0x27;
        static const uint8_t CMD_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL = 0x29;
        static const uint8_t CMD_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL  = 0x2A;

        c_i2c & r_i2c;
        uint8_t address;
        uint8_t offset_x;
        uint8_t contrast_normal;
        uint8_t contrast_dimmed;
        uint8_t dot_size;
        uint8_t current_x;
        uint8_t current_y;
        uint8_t cursor_x;
        uint8_t cursor_y;
        bool    cursor_on;
        vcc_source_t vcc_source;
        c_font_h5_v8 font_h5_v8 = c_font_h5_v8();

};

#endif //SSD1306_SH1106_TEXT_DISPLAY_H
