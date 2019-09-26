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


#### *void set_contrast(uint8_t contrast, uint8_t contrast_dimm);*  


#### *void clear(void);*  


#### *void power_on(bool power);*  


#### *void dim(bool dim);*  


#### *void print_char(char ch);*  


#### *void print_number(uint16_t number, uint8_t width);*  


#### *void print(char * p_str);*  


#### *void println(char * p_str);*  


#### *void set_font_size(uint8_t size);*  


#### *void set_possition(uint8_t position_x, uint8_t position_y);*  


#### *void show_cursor(uint8_t position_x, uint8_t position_y);*  


#### *void hide_cursor(void);*  



