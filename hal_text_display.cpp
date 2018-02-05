#include <stdint.h>
#include <arduino.h>
#include "font_h6_v8.h"
#include "hal_text_display.h"


c_text_display::c_text_display(c_i2c & ref_i2c, uint8_t i2c_address) :
                               r_i2c(ref_i2c), address(i2c_address),
                               current_x(0u), current_y(0u),
                               vcc_source(SSD1306_VCC_EXTERNAL)
{
    
}


void c_text_display::init(vcc_source_t vcc)
{
    vcc_source = vcc;

    // Init sequence
    send_command(SSD1306_CMD_DISPLAYOFF);           // 0xAE
    send_command(SSD1306_CMD_SETDISPLAYCLOCKDIV);   // 0xD5
    send_command(0x80);                             // the suggested ratio 0x80
    send_command(SSD1306_CMD_SETMULTIPLEX);         // 0xA8
    send_command(SSD1306_LCD_HEIGHT - 1);
    send_command(SSD1306_CMD_SETDISPLAYOFFSET);     // 0xD3
    send_command(0x0);                              // no offset
    send_command(SSD1306_CMD_SETSTARTLINE | 0x0);   // line #0
    send_command(SSD1306_CMD_CHARGEPUMP);           // 0x8D
    send_command((SSD1306_VCC_EXTERNAL == vcc_source) ? (0x10) : (0x14));     
    send_command(SSD1306_CMD_MEMORYMODE);           // 0x20
    send_command(0x00);                             // 0x0 act like ks0108
    send_command(SSD1306_CMD_SEGREMAP | 0x1);
    send_command(SSD1306_CMD_COMSCANDEC);
    send_command(SSD1306_CMD_SETCOMPINS);           // 0xDA
    send_command(0x12);
    send_command(SSD1306_CMD_SETCONTRAST);          // 0x81
    send_command((SSD1306_VCC_EXTERNAL == vcc_source) ? (0x9F) : (0xCF));     
    send_command(SSD1306_CMD_SETPRECHARGE);         // 0xd9
    send_command((SSD1306_VCC_EXTERNAL == vcc_source) ? (0x22) : (0xF1));     
    send_command(SSD1306_CMD_SETVCOMDETECT);        // 0xDB
    send_command(0x40);
    send_command(SSD1306_CMD_DISPLAYALLON_RESUME);  // 0xA4
    send_command(SSD1306_CMD_NORMALDISPLAY);        // 0xA6
    send_command(SSD1306_CMD_DEACTIVATE_SCROLL);
    send_command(SSD1306_CMD_DISPLAYON);            //--turn on oled panel

    clear();
}


void c_text_display::clear(void)
{
    set_possition(0u, 0u);
    
    for (uint8_t index = 0u; index < (SSD1306_LCD_BUFFER_SIZE / 16u); index++)
    {
        send_data_start();

        for (uint8_t index_2 = 0u; index_2 < 16u; index_2++)
        {
            send_data_byte(0x00u);
        }

        send_data_end();
    }
        
    set_possition(0u, 0u);
    set_cursor(0u, 0u);
}


void c_text_display::dim(bool dim)
{
    send_command(SSD1306_CMD_SETCONTRAST);
    send_command(dim ? 0u : ((SSD1306_VCC_EXTERNAL == vcc_source) ? (0x9F) : (0xCF)));
}


void c_text_display::print_char(char ch)
{
    uint8_t  byte = 0u;
    uint8_t  bit  = 0u;
    uint32_t tmp  = 0u;

    for (uint8_t index = 0u; index < 6u; index++)
    {
        tmp = (uint32_t)0u;
        byte = pgm_read_byte_near(&font_h6_v8[ch - (' ')][index]);

        // Multiply dots for bigger fonts.
        for (uint8_t bit_number = 0; bit_number < 8u; bit_number++)
        {
            bit = (byte & (0x01u << bit_number)) >> bit_number;

            if (0u == dot_size)
            {
                tmp = byte;
            }
            else
            {
                for (uint8_t bit_repetition = 0u; bit_repetition < dot_size; bit_repetition++)
                {
                    tmp |= (uint32_t)bit << ((bit_number * dot_size) + bit_repetition );
                }
            }
        }

        // Send to display.
        for (uint8_t row = 0; row < dot_size; row++)
        {
            set_possition(((index * dot_size) + (current_x * dot_size * 6u)), 
                          (row + (current_y * dot_size)));
            send_data_start();

            for (uint8_t column = 0; column < dot_size; column++)
            {
                uint8_t tmp_byte = (uint8_t)((tmp & ((uint32_t)0xFFu << (row * 8u))) >> (row * 8u));

                send_data_byte(tmp_byte);
            }

            send_data_end();
        }
    }
}


void c_text_display::print(char * p_str)
{
    uint8_t index = 0u;

    while ('\0' != p_str[index])
    {
        if ((SSD1306_LCD_WIDTH / (dot_size * 6u)) <= current_x)
        {
            current_x = 0u;
            current_y++; 
        }

        print_char(p_str[index]);
        index++;
        current_x++;

        set_cursor(current_x, current_y);
    }
}


void c_text_display::println(char * p_str)
{
    print(p_str);
    current_x = 0u;
    current_y++; 
    set_cursor(current_x, current_y);
}


void c_text_display::set_font_size(uint8_t size)
{
    dot_size = ((0u == size) || (1u == size)) ? (size + 1u) : 4u;
}


void c_text_display::set_possition(uint8_t position_x, uint8_t position_y)
{
    send_command(SSD1306_CMD_COLUMNADDR);
    send_command(position_x);
    send_command(SSD1306_LCD_WIDTH - 1u);
    send_command(SSD1306_CMD_PAGEADDR);
    send_command(position_y);
    send_command((SSD1306_LCD_HEIGHT / 8u) - 1);
}

void c_text_display::set_cursor(uint8_t position_x, uint8_t position_y)
{    
    current_x = position_x; 
    current_y = position_y;
}


void c_text_display::show_cursor(uint8_t position_x, uint8_t position_y)
{

}


void c_text_display::send_command(uint8_t command)
{
    r_i2c.transfer_begin(address);
    r_i2c.transfer_byte(0x00u);  // send 0x00 for command, 
    r_i2c.transfer_byte(command);
    r_i2c.transfer_end();
}


void c_text_display::send_data_start(void)
{
    r_i2c.transfer_begin(address);
    r_i2c.transfer_byte(0x40u);  // send 0x40 for data, 
}


void c_text_display::send_data_byte(uint8_t data_byte)
{
    r_i2c.transfer_byte(data_byte);
}


void c_text_display::send_data_end(void)
{
    r_i2c.transfer_end();
}
