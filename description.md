# SSD1306_SH1106_i2c_text_display
A text only driver for oled displays based on the SSD1306 or SH1106 controllers.

<!-- ======================================================================= -->
<!-- ======================================================================= -->

## *SSD1306_SH1106_i2c_text_display.h*:   
Provides the class *'c_SSD1306_SH1106_i2c'* - an easy way to visualise text on a display with one of the aforementioned controllers. It has a small RAM footprint by not using a RAM buffer, but writing directly to the display's controller directly.


#### *c_SSD1306_SH1106_i2c(c_i2c & ref_i2c, uint8_t i2c_address);*  
Constructor, parameters are:  
*`ref_i2c`* - *`c_i2c`* object by reference. This it the interface through which the microcontroller is going to communicate to the EEPROM chip. The *'c_i2c'* class could be found in *'hal_avr_i2c.h'* from the [**hal_lib_cpp library**](https://github.com/deelbg/hal_lib_avr_cpp).  
*`i2c_address`* - the i2c address of the EEPROM chip.


#### *void init(vcc_source_t vcc);*  
Initialisation function. Sends the necessary commands to the display controller in order to set it in an operational state.  
*`vcc`* a parameter of type *`vcc_source_t`*. Has two possible values: *VCC_EXTERNAL* or *VCC_SWITCHCAP*. It defines whether the voltage for the LEDs is externally provided or raised internally.  


#### *void set_offset_x(uint8_t offset);*  
Sets an offset in pixels on the x axis. The default value is 0. This offset shifts the used area of the display controller memory with *`offset`* pixels the the right.  
This function must be used when the first row of LEDs is not mapped to the first column in memory. This is the case with some 1.3 inch, 128x64 displays that use the SH1106 controller.


#### *void set_contrast(uint8_t contrast, uint8_t contrast_dim);*  
Overrides the defaults for contrast values of the display in normal and dimmed mode.  
*`contrast`* - contrast in normal mode.  
*`contrast_dim`* - contrast in dimmed mode.  


#### *void clear(void);*  
Clears the entire display and positions the cursor at x=0 and y=0.  


#### *void power_on(bool power);*  
Powers on/off the display.  
*`power = true;`* - Powers on the display.  
*`power = false;`* - Powers off the display and reduces its power consumption.  


#### *void dim(bool dim);*  
Dims the display by changing it's contrast.  
*`dim = true;`* - reduce the contrast, sets the display contrast to the value give to the *`contrast_dim`* parameter of the *`set_contrast()`* function.  
*`dim = false;`* - increase the contrast, sets the display contrast to the value give to the *`contrast`* parameter of the *`set_contrast()`* function.  


#### *void print_char(char ch);*  
Prints a string character *`ch`* at the current position set by a call to the *`set_possition()`* function.

#### *void print_number(uint16_t number, uint8_t width);*  
Prints an integer number *`number`* at the current position set by a call to the *`set_possition()`* function.  
*`width`* - determines how many character the printed number will take. Fixed width. The number os padded with spaces on the left if needed. The idea of this function is to avoid the usage of *`sprintf()`* calls for printing out a simple integer number, since it has rather large program memory footprint. 

#### *void print(char * p_str);*  
Prints a string, pointed by *`p_str`*, starting at the current position set by a call to the *`set_possition()`* function.

#### *void println(char * p_str);*  
Prints a string, pointed by *`p_str`*, starting at the current position set by a call to the *`set_possition()`* function. After that sends the position to the beginning of the next line.


#### *void set_font_size(uint8_t size);*  
Sets the font size to be used.  
*`size`* - A value from 0 to 2, if greater value is passed the biggest font will be used, i.e. 2.  
*`size = 0;`* - The smallest font is 8 by 5 pixels. On a 128x64 pixel display there will be 8 lines of 25 characters.  
*`size = 1;`* - Font is 16 by 10 pixels. On a 128x64 pixel display there will be 4 lines of 10 characters.  
*`size = 2;`* - Font is 32 by 20 pixels. On a 128x64 pixel display there will be 2 lines of 5 characters.  


#### *void set_possition(uint8_t position_x, uint8_t position_y);*  
Sets the position from which the next *`print()`* is going to execute. The position is indicated in line *`position_y`* and character number - *`position_x`*, not in pixels. That is why the maximal *`position_x`* and *`position_y`* depend on the font size that have been set using *`set_font_size()`* and is active at the moment. Position x=0; y=0; is in the top left corner of the display.


#### *void show_cursor(uint8_t position_x, uint8_t position_y);*  
Shows a cursor, i.e. underscores the symbol at position *`position_x`* and *`position_y`*.  
The display is not refreshed immediately, on a following *`print()`* over the cursor's position, the printed character will be underscored.  


#### *void hide_cursor(void);*  
Hides the cursor form the display if it has been activated using the previous function.  
The display is not refreshed immediately, on a following *`print()`* over the cursor's position, the printed character will be displayed without an underscored.  


