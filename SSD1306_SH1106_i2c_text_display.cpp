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


#include <stdint.h>
#include "font_h5_v8.h"
#include "SSD1306_SH1106_i2c_text_display.h"


c_SSD1306_SH1106_i2c::c_SSD1306_SH1106_i2c(c_i2c & ref_i2c, uint8_t i2c_address) :
                               r_i2c(ref_i2c), address(i2c_address),
                               offset_x(0u), contrast_normal(0x9F), contrast_dimmed(0x00),
                               dot_size(1u), current_x(0u), current_y(0u),
                               cursor_x(0u), cursor_y(0u), cursor_on(false),
                               vcc_source(VCC_EXTERNAL)
{
    
}


void c_SSD1306_SH1106_i2c::init(vcc_source_t vcc)
{
    vcc_source = vcc;

    r_i2c.start_write(address);
    r_i2c.write_byte(COMMAND);

    r_i2c.write_byte(CMD_DISPLAY_OFF);
    r_i2c.write_byte(CMD_NORMAL_DISPLAY);
    r_i2c.write_byte(CMD_SET_DISPLAY_CLOCK_DIV);
    r_i2c.write_byte(0x80);
    r_i2c.write_byte(CMD_SET_MULTIPLEX);
    r_i2c.write_byte(LCD_HEIGHT - 1);
    r_i2c.write_byte(CMD_SET_DISPLAY_OFFSET);
    r_i2c.write_byte(0x0);
    r_i2c.write_byte(CMD_SET_START_LINE_NUMBER | 0x0);
    r_i2c.write_byte(CMD_CHARGE_PUMP);
    r_i2c.write_byte((VCC_EXTERNAL == vcc_source) ? (0x10) : (0x14));     
    r_i2c.write_byte(CMD_MEMORY_MODE);
    r_i2c.write_byte(0x00);
    r_i2c.write_byte(CMD_SEGMENT_REMAP | 0x1);
    r_i2c.write_byte(CMD_COM_SCAN_DEC);
    r_i2c.write_byte(CMD_SET_COM_PINS);
    r_i2c.write_byte(0x12);
    r_i2c.write_byte(CMD_SET_CONTRAST);
    r_i2c.write_byte(contrast_normal);     
    r_i2c.write_byte(CMD_SET_PRECHARGE);
    r_i2c.write_byte((VCC_EXTERNAL == vcc_source) ? (0x22) : (0xF1));     
    r_i2c.write_byte(CMD_SET_V_COM_DETECT);
    r_i2c.write_byte(0x40);
    r_i2c.write_byte(CMD_DISPLAY_ALL_ON_RESUME);
    r_i2c.write_byte(CMD_NORMAL_DISPLAY);
    r_i2c.write_byte(CMD_DEACTIVATE_SCROLL);
    r_i2c.write_byte(CMD_DISPLAY_ON);

    r_i2c.stop();
    clear();
}


void c_SSD1306_SH1106_i2c::set_contrast(uint8_t contrast, uint8_t contrast_dimm)
{

    contrast_normal = contrast;
    contrast_dimmed = contrast_dimm;

    r_i2c.start_write(address);
    r_i2c.write_byte(COMMAND);
    r_i2c.write_byte(CMD_SET_CONTRAST);
    r_i2c.write_byte(contrast_normal);     
    r_i2c.stop();
}


void c_SSD1306_SH1106_i2c::set_offset_x(uint8_t offset)
{
    offset_x = offset;
}


void c_SSD1306_SH1106_i2c::clear(void)
{
    set_possition_raw(offset_x, 0u);
    
    for (uint8_t index_y = 0u; index_y <= (LCD_HEIGHT / 8u); index_y++)
    {
        r_i2c.start_write(address);
        r_i2c.write_byte(DATA);

        for (uint8_t index_x = 0u; index_x < LCD_WIDTH; index_x++)
        {
            r_i2c.write_byte(0x00);
        }

        r_i2c.stop();

        set_possition_raw(offset_x, index_y);
    }
        
    set_possition_raw(offset_x, 0u);
    set_possition(0u, 0u);
}


void c_SSD1306_SH1106_i2c::power_on(bool power)
{

    r_i2c.start_write(address);
    r_i2c.write_byte(COMMAND);
    r_i2c.write_byte((power ? CMD_DISPLAY_ON : CMD_DISPLAY_OFF));
    r_i2c.stop();
}


void c_SSD1306_SH1106_i2c::dim(bool dim)
{
    r_i2c.start_write(address);
    r_i2c.write_byte(COMMAND);
    r_i2c.write_byte(CMD_SET_CONTRAST);
    r_i2c.write_byte(dim ? contrast_dimmed : contrast_normal);
    r_i2c.stop();
}


void c_SSD1306_SH1106_i2c::print_char(char ch)
{
    uint8_t  byte       = 0u;
    uint8_t  bit        = 0u;
    uint32_t tmp        = 0u;
    uint8_t  tmp_byte   = 0u;

    for (uint8_t index = 0u; index < 6u; index++)
    {
        tmp = (uint32_t)0u;
        
        byte = (0u == index) ? 0x00u : font_h5_v8.get_char_column(ch, (index - 1));

        if (cursor_on && (current_x == cursor_x) && (current_y == cursor_y))
        {
            byte |= 0x80u;
        }
                
        // Multiply pixel for larger font sizes.
        for (uint8_t bit_number = 0; bit_number < 8u; bit_number++)
        {
            bit = (byte & (0x01u << bit_number)) >> bit_number;

            for (uint8_t bit_repetition = 0u; bit_repetition < dot_size; bit_repetition++)
            {
                tmp |= (uint32_t)bit << ((bit_number * dot_size) + bit_repetition );
            }
        }

        // Send to display.
        for (uint8_t row = 0; row < dot_size; row++)
        {
            set_possition_raw((offset_x + (index * dot_size) + (current_x * dot_size * 6u)), (row + (current_y * dot_size)));
            
            r_i2c.start_write(address);
            r_i2c.write_byte(DATA);
                
            tmp_byte = (uint8_t)((tmp & ((uint32_t)0xFFu << (row * 8u))) >> (row * 8u));
        
            for (uint8_t column = 0; column < dot_size; column++)
            {
                r_i2c.write_byte(tmp_byte);        
            }

            r_i2c.stop();
        }
    }
}

       
void c_SSD1306_SH1106_i2c::print_number(uint16_t number, uint8_t width)
{   
    const uint8_t MAX_LEN = 5u;
    const uint16_t dividers[MAX_LEN] = {10000u, 1000u, 100u, 10u, 1u};    
    char    buff[MAX_LEN+1];
    uint8_t digit = 0;
    uint8_t first_digit_position = 255u;
    uint8_t print_position = 0u;
    uint8_t print_width = MAX_LEN <= width ? MAX_LEN: width;


    for (uint8_t position = 0u; position < MAX_LEN; position++)
    {   
        digit = (number / dividers[position]) % 10u;
        
        if ((0u != digit) && (255u == first_digit_position))
        {
            first_digit_position = position;
        }

        buff[position] = (255u != first_digit_position) ? '0' + digit : ' ' ;
    }

    buff[4u] = (char)('0' + number % 10u);
    buff[5u] = '\0';

    if ((MAX_LEN - first_digit_position) > print_width)
    {
        print_position = first_digit_position;
    }
    else
    {
        print_position = (MAX_LEN - print_width);
    }

    print(&buff[print_position]);
}


void c_SSD1306_SH1106_i2c::print(char * p_str)
{
    uint8_t index = 0u;

    while ('\0' != p_str[index])
    {
        if ((LCD_WIDTH / (dot_size * 6u)) <= current_x)
        {
            current_x = 0u;
            current_y++; 
        }

        print_char(p_str[index]);
        index++;
        current_x++;

        set_possition(current_x, current_y);
    }
}


void c_SSD1306_SH1106_i2c::println(char * p_str)
{
    print(p_str);
    current_x = 0u;
    current_y++; 
    set_possition(current_x, current_y);
}


void c_SSD1306_SH1106_i2c::set_font_size(uint8_t size)
{
    dot_size = ((0u == size) || (1u == size)) ? (size + 1u) : 4u;
}


void c_SSD1306_SH1106_i2c::set_possition_raw(uint8_t position_x, uint8_t position_y)
{
    send_command(CMD_SET_PAGE_START_ADDRESS | (position_y & 0x0F));
    send_command(CMD_SET_COLUMN_NUMBER_LOW  | (position_x & 0x0F));
    send_command(CMD_SET_COLUMN_NUMBER_HIGH | ((position_x & 0xF0) >> 4u));
    send_command(CMD_SET_START_LINE_NUMBER | 0x00);
}

void c_SSD1306_SH1106_i2c::set_possition(uint8_t position_x, uint8_t position_y)
{    
    current_x = position_x;
    current_y = position_y;
}


void c_SSD1306_SH1106_i2c::show_cursor(uint8_t position_x, uint8_t position_y)
{
    cursor_on = true;
    cursor_x = position_x;
    cursor_y = position_y;
}

void c_SSD1306_SH1106_i2c::hide_cursor(void)
{
    cursor_on = false;
}


void c_SSD1306_SH1106_i2c::send_command(uint8_t command)
{
    r_i2c.start_write(address);
    r_i2c.write_byte(COMMAND); 
    r_i2c.write_byte(command);
    r_i2c.stop();
}


void c_SSD1306_SH1106_i2c::send_data(uint8_t data_byte)
{
    r_i2c.start_write(address);
    r_i2c.write_byte(DATA);
    r_i2c.write_byte(data_byte);
    r_i2c.stop();
}
