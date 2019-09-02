#include <stdint.h>
#include "hal_avr_i2c.h"
#include "SSD1306_i2c_text_display.h"

static const uint32_t CPU_FREQUENCY = 16000000u;
static const uint32_t I2C_FREQUENCY = 400000u;
static const uint8_t  OLED_ADDRESS  = 0x3Cu;

c_i2c g_i2c = c_i2c();
c_SSD1306_i2c_text_display g_display = c_SSD1306_i2c_text_display(g_i2c, OLED_ADDRESS);

void setup()
{
    g_i2c.init();
    g_display.init(c_SSD1306_i2c_text_display::VCC_SWITCHCAP);
}


void loop()
{
    // Clear the screen and 
    // position cursor at upper left corner x=0 and y=0.
    g_display.clear();
    
    // Set font to the middle size.
    g_display.set_font_size(1);

    // Position cursor. Position is in lines and characters 
    // based on the selected font size.
    g_display.set_possition(5, 1);

    // Print a single character at the previously set position.
    g_display.print_char('A');    
    delay(5000);
        
    // Print a number with different width.
    g_display.clear();
    g_display.set_possition(0, 0);
    g_display.print_number(1, 4);

    g_display.set_possition(0, 1);
    g_display.print_number(12, 4);

    g_display.set_possition(0, 2);
    g_display.print_number(123, 4);

    g_display.set_possition(0, 3);
    g_display.print_number(12345, 4);
    delay(5000);

    // Print strings in english and in cyrillic.
    // For the cyrillic to display propperly,
    // the file must be saved in "Windows CP1251" encoding 
    // as this is the encoding of the font.

    // Display all characters of the font with font size 0 and 1.
    for (uint8_t size = 0; size < 2; size++)
    {
        g_display.set_font_size(size);
        
        g_display.clear();
        g_display.print("TEST");
        g_display.println("1");
        g_display.println("TEST2");
        g_display.println("ÀÁÂÃÄÅÆÇÈÉ");
        g_display.print("àáâãäåæçèé");
        delay(5000);

        g_display.clear();
        g_display.print(" !\"#$%&'()*+,-./0123456789:;<=>?@");
        delay(5000);

        g_display.clear();
        g_display.print("ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`");
        delay(5000);

        g_display.clear();
        g_display.print("abcdefghijklmnopqrstuvwxyz");
        delay(5000);

        g_display.clear();
        g_display.print("ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖ×ØÙÚÛÜİŞß");        
        delay(5000);
        
        g_display.clear();
        g_display.print("àáâãäåæçèéêëìíîïğñòóôõö÷øùúûüışÿ");    
        delay(5000);
    }

    // Show a cursor on the screen.
    // The character at the selected position gets underlined.
    // The cursor will not move automatically.
    g_display.clear();
    g_display.set_font_size(2);
    g_display.show_cursor(3, 0);    
    g_display.print("TEST3");
    delay(2000);

    // Hide the cursor.
    g_display.set_possition(0, 0);
    g_display.hide_cursor();    
    g_display.print("TEST3");
    delay(2000);

    // Dim on and off the display.
    g_display.dim(true);
    delay(2000);
    g_display.dim(false);
    delay(2000);
    g_display.dim(true);
    delay(2000);
    g_display.dim(false);
    delay(2000);
}
