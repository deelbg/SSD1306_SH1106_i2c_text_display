#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "hal_text_display.h"

Adafruit_SSD1306 g_adafruit_display = Adafruit_SSD1306(4);
c_text_display g_display = c_text_display(g_adafruit_display, 0x3Cu, 2u);

uint8_t counter = 0u;
char str_buff[11] = {};

void setup()
{
    g_adafruit_display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    g_adafruit_display.display();
    g_display.clear(); 
}



void loop()
{
    // g_adafruit_display.clearDisplay();
    // g_adafruit_display.setTextSize(1);
    // g_adafruit_display.setTextColor(WHITE);
    // g_adafruit_display.setCursor(0,0);
    // g_adafruit_display.println("Hello, world!");
    // g_adafruit_display.setTextColor(BLACK, WHITE); // 'inverted' text
    // g_adafruit_display.println(3.141592);
    // g_adafruit_display.setTextSize(2);
    // g_adafruit_display.setTextColor(WHITE);
    // g_adafruit_display.print("0x"); 
    // g_adafruit_display.println(0xDEADBEEF, HEX);
    // g_adafruit_display.display();
    // delay(2000);

    g_display.clear(); 
    // g_display.set_possition(0,0);

    // sprintf(str_buff, "test: ");
    // g_display.print(str_buff);
    
    // sprintf(str_buff, "run number");
    // g_display.println("str_buff");
    
    // sprintf(str_buff, "%d", counter);
    // g_display.println(str_buff);
    
    // g_display.set_cursor(2u, 3u);
    
    // g_display.show();

    // counter++;

    delay(2000);
}
