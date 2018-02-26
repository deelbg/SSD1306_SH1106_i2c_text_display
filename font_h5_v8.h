#ifndef font_h5_v8_H
#define font_h5_v8_H

#define font_h5_v8_VERSION_MAJOR 1
#define font_h5_v8_VERSION_MINOR 0


class c_font_h5_v8
{
    public:

        c_font_h5_v8();
        
        // The charcters are 8 points hight and 6 points wide.
        // Each character is described by 6 bytes, 
        // where each byte is one column of the character. 
        // This function returns one column of a character.
        // It accepts the "ASCII 1251" of a char and the number of the column needed.
        // If the character is not included in the font it will be treated as a space.
        uint8_t get_char_column(char ch, uint8_t column);
                
    private:

};

#endif //font_h5_v8_H
