#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "hal_text_display.h"

c_text_display g_display = c_text_display(0x3Cu, 2u);

uint8_t counter = 0u;
char str_buff[11] = {};

void setup()
{
    g_display.init();
}



void loop()
{
    g_display.clear(); 
    g_display.set_possition(0,0);

    sprintf(str_buff, "test: ");
    g_display.print(str_buff);
    
    sprintf(str_buff, "run number");
    g_display.println(str_buff);
    
    sprintf(str_buff, "%d", counter);
    g_display.println(str_buff);
    
    g_display.set_cursor(2u, 3u);
    
    g_display.show();

    counter++;

    delay(1000);
}
