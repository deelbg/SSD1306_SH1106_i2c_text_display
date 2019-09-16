# SSD1306_SH1106_i2c_text_display
SSD1306_SH1106_i2c_text_display

<!-- ======================================================================= -->
<!-- ======================================================================= -->

## *SSD1306_SH1106_i2c_text_display.h* - Digital IO driver: 
Brief describtion.

#### *c_SSD1306_SH1106_i2c(c_i2c & ref_i2c, uint8_t i2c_address);*  
The constructor.

#### *void init(vcc_source_t vcc);*  


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


