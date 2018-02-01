#include <stdint.h>
#include "hal_text_display.h"


c_text_display::c_text_display(c_i2c & ref_i2c, uint8_t i2c_address) :
                               r_i2c(ref_i2c), address(i2c_address)                               
{
    
}


void c_text_display::init(vcc_source_t vcc_source)
{
    // Init sequence
    send_command(SSD1306_CMD_DISPLAYOFF);           // 0xAE
    send_command(SSD1306_CMD_SETDISPLAYCLOCKDIV);   // 0xD5
    send_command(0x80);                             // the suggested ratio 0x80
    send_command(SSD1306_CMD_SETMULTIPLEX);         // 0xA8
    send_command(SSD1306_CMD_LCDHEIGHT - 1);
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

    delay(200);

    display.clearDisplay();
    display.setTextColor(WHITE, BLACK);
    display.setCursor(0,0);
    display.print("test");
    display.display();   

    delay(2000);

    display.begin(SSD1306_SWITCHCAPVCC, address);
    display.clearDisplay();
    display.setTextColor(WHITE, BLACK);
    display.setCursor(0,0);
    display.print("test");
    display.display(); 

    delay(2000);  
}


void c_text_display::clear(void)
{
    display.clearDisplay();    
    display.setTextSize(font_size);
    display.setTextColor(WHITE, BLACK);
}



void c_text_display::dim(bool dim)
{
    display.dim(dim);
}


void c_text_display::show(void)
{
    display.display();
}


void c_text_display::print(char * p_str)
{
    display.print(p_str);
}


void c_text_display::println(char * p_str)
{
    display.println(p_str);
}


void c_text_display::set_font_size(uint8_t size)
{
    font_size = ( 3u >= size) ? size : 3u;
    display.setTextSize(font_size);
}


void c_text_display::set_possition(uint8_t position_x, uint8_t position_y)
{
    display.setCursor((position_x * 12u), (position_y * 16u));
}


void c_text_display::set_cursor(uint8_t position_x, uint8_t position_y)
{
    for (uint8_t index = 0; index < 3; index++)
    {
        display.drawLine((position_x * 12), ((position_y * 16) + (16 - index)), 
                           ((position_x * 12) + 10), ((position_y * 16) + (16 - index)), WHITE);
    }
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
