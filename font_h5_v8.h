// ==============================================================================
// MIT License

// Copyright (c) 2019 Deyan Todorov

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// ==============================================================================


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
