#include <stdint.h>
#include "font_h5_v8.h"
#include "SSD1306_i2c_text_display.h"


c_SSD1306_i2c_text_display::c_SSD1306_i2c_text_display(c_i2c_usi & ref_i2c, uint8_t i2c_address) :
                               r_i2c(ref_i2c), address(i2c_address),
                               dot_size(1u), current_x(0u), current_y(0u),
                               cursor_x(0u), cursor_y(0u), cursor_on(false),
                               vcc_source(VCC_EXTERNAL)
{
    
}


void c_SSD1306_i2c_text_display::init(vcc_source_t vcc)
{
    vcc_source = vcc;

    r_i2c.start_write(address);
    r_i2c.write_byte(COMMAND);

    // Init sequence
    r_i2c.write_byte(CMD_DISPLAYOFF);           // 0xAE
    r_i2c.write_byte(CMD_SETDISPLAYCLOCKDIV);   // 0xD5
    r_i2c.write_byte(0x80);                     // the suggested ratio 0x80
    r_i2c.write_byte(CMD_SETMULTIPLEX);         // 0xA8
    r_i2c.write_byte(LCD_HEIGHT - 1);
    r_i2c.write_byte(CMD_SETDISPLAYOFFSET);     // 0xD3
    r_i2c.write_byte(0x0);                      // no offset
    r_i2c.write_byte(CMD_SETSTARTLINE | 0x0);   // line #0
    r_i2c.write_byte(CMD_CHARGEPUMP);           // 0x8D
    r_i2c.write_byte((VCC_EXTERNAL == vcc_source) ? (0x10) : (0x14));     
    r_i2c.write_byte(CMD_MEMORYMODE);           // 0x20
    r_i2c.write_byte(0x00);                     // 0x0 act like ks0108
    r_i2c.write_byte(CMD_SEGREMAP | 0x1);
    r_i2c.write_byte(CMD_COMSCANDEC);
    r_i2c.write_byte(CMD_SETCOMPINS);           // 0xDA
    r_i2c.write_byte(0x12);
    r_i2c.write_byte(CMD_SETCONTRAST);          // 0x81
    r_i2c.write_byte((VCC_EXTERNAL == vcc_source) ? (0x9F) : (0xCF));     
    r_i2c.write_byte(CMD_SETPRECHARGE);         // 0xd9
    r_i2c.write_byte((VCC_EXTERNAL == vcc_source) ? (0x22) : (0xF1));     
    r_i2c.write_byte(CMD_SETVCOMDETECT);        // 0xDB
    r_i2c.write_byte(0x40);
    r_i2c.write_byte(CMD_DISPLAYALLON_RESUME);  // 0xA4
    r_i2c.write_byte(CMD_NORMALDISPLAY);        // 0xA6
    r_i2c.write_byte(CMD_DEACTIVATE_SCROLL);
    r_i2c.write_byte(CMD_DISPLAYON);            //--turn on oled panel

    r_i2c.stop();

    clear();
}


void c_SSD1306_i2c_text_display::clear(void)
{
    set_possition_raw(0u, 0u);
    
    for (uint8_t index = 0u; index < (LCD_BUFFER_SIZE / 16u); index++)
    {
        r_i2c.start_write(address);
        r_i2c.write_byte(DATA);

        for (uint8_t index_2 = 0u; index_2 < 16u; index_2++)
        {
            r_i2c.write_byte(0x00u);
        }

        r_i2c.stop();
    }
        
    set_possition_raw(0u, 0u);
    set_possition(0u, 0u);
}


void c_SSD1306_i2c_text_display::power_on(bool power)
{

    r_i2c.start_write(address);
    r_i2c.write_byte(COMMAND);
    r_i2c.write_byte((power ? CMD_DISPLAYON : CMD_DISPLAYOFF));
    r_i2c.stop();
}


void c_SSD1306_i2c_text_display::dim(bool dim)
{
    r_i2c.start_write(address);
    r_i2c.write_byte(COMMAND);
    r_i2c.write_byte(CMD_SETCONTRAST);
    r_i2c.write_byte(dim ? 0u : ((VCC_EXTERNAL == vcc_source) ? (0x9F) : (0xCF)));
    r_i2c.stop();
}


void c_SSD1306_i2c_text_display::print_char(char ch)
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
            set_possition_raw(((index * dot_size) + (current_x * dot_size * 6u)), (row + (current_y * dot_size)));
            
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

       
void c_SSD1306_i2c_text_display::print_number(uint16_t number, uint8_t width)
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


void c_SSD1306_i2c_text_display::print(char * p_str)
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


void c_SSD1306_i2c_text_display::println(char * p_str)
{
    print(p_str);
    current_x = 0u;
    current_y++; 
    set_possition(current_x, current_y);
}


void c_SSD1306_i2c_text_display::set_font_size(uint8_t size)
{
    dot_size = ((0u == size) || (1u == size)) ? (size + 1u) : 4u;
}


void c_SSD1306_i2c_text_display::set_possition_raw(uint8_t position_x, uint8_t position_y)
{
    r_i2c.start_write(address);
    r_i2c.write_byte(COMMAND);
    r_i2c.write_byte(CMD_COLUMNADDR);
    r_i2c.write_byte(position_x);
    r_i2c.write_byte(LCD_WIDTH - 1u);
    r_i2c.write_byte(CMD_PAGEADDR);
    r_i2c.write_byte(position_y);
    r_i2c.write_byte((LCD_HEIGHT / 8u) - 1);
    r_i2c.stop();
}

void c_SSD1306_i2c_text_display::set_possition(uint8_t position_x, uint8_t position_y)
{    
    current_x = position_x;
    current_y = position_y;
}


void c_SSD1306_i2c_text_display::show_cursor(uint8_t position_x, uint8_t position_y)
{
    cursor_on = true;
    cursor_x = position_x;
    cursor_y = position_y;
}

void c_SSD1306_i2c_text_display::hide_cursor(void)
{
    cursor_on = false;
}


void c_SSD1306_i2c_text_display::send_command(uint8_t command)
{
    r_i2c.start_write(address);
    r_i2c.write_byte(0x00u);  // send 0x00 for command, 
    r_i2c.write_byte(command);
    r_i2c.stop();
}
