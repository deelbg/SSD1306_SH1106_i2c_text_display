# SSD1306_SH1106_i2c_text_display
A text only driver for oled displays based on the SSD1306 or SH1106 controllers.  
The class **c_SSD1306_SH1106_i2c** provides easy way to visualise text on one of those displays. The main goal was to have a driver with very small memory (RAM) footprint which allows the usage of those OLED displays with small microcontrollers that do not have a lot of RAM. This is accomplished by not using a memory and directly writing to the display's memory instead.  
The driver comes together with a font 8 by 5 pixels which includes Cyrillic symbols as well.
Complete description of the classe public interface is provided in [**description.md**](./description.md). 



### Examples:  
Example of the driver usage is given in an Arduino sketch [**SSD1306_SH1106_i2c_text_display.ino**](./SSD1306_SH1106_i2c_text_display.ino). Example explanations are in the comments. 
The example sketch shows all the functionality of the driver, writing text in both engllish and cyrillic. Numbers with predefined width and shows the font sizes that are available. 

![GitHub Logo](/IMG_2129.JPG) ![GitHub Logo](/IMG_2131.JPG) 

### License:  
MIT License for open source software. The complete text of the license might be found in the [**LICENSE**](./LICENSE) file. 
