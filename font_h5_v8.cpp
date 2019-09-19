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


#include <avr/pgmspace.h>
#include "font_h5_v8.h"

// http://ascii-table.com/codepage.php?1251
// 1251 ascii table is partially implemented.
// There are 2 fonts, Cyrillic and English.
// 
// The english includes the standart 127 symbol
// ascii table excluding the first 32 controll characters.
// 
// |--------------------------------------------------------------------|
// |    |x0 |x1 |x2 |x3 |x4 |x5 |x6 |x7 |x8 |x9 |xA |xB |xC |xD |xE |xF |
// |----|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
// | 2x |sp | ! | " | # | $ | % | & | ' | ( | ) | * | + | , | - | . | / |
// |----|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
// | 3x | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | : | ; | < | = | > | ? |
// |----|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
// | 4x | @ | A | B | C | D | E | F | G | H | I | J | K | L | M | N | O |
// |----|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
// | 5x | P | Q | R | S | T | U | V | W | X | Y | Z | [ | \ | ] | ^ | _ |
// |----|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
// | 6x | ` | a | b | c | d | e | f | g | h | i | j | k | l | m | n | o |
// |----|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
// | 7x | p | q | r | s | t | u | v | w | x | y | z | { | | | } | ~ |   |
// |--------------------------------------------------------------------|
//  
// The Cyrillic fornt implements only characters form 0xC0 to 0xFF, 
// i.e. small and capital letters
// 
// |--------------------------------------------------------------------|
// |    |x0 |x1 |x2 |x3 |x4 |x5 |x6 |x7 |x8 |x9 |xA |xB |xC |xD |xE |xF |
// |----|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
// | Cx | À | Á | Â | Ã | Ä | Å | Æ | Ç | È | É | Ê | Ë | Ì | Í | Î | Ï |
// |----|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
// | Dx | Ð | Ñ | Ò | Ó | Ô | Õ | Ö | × | Ø | Ù | Ú | Û | Ü | Ý | Þ | ß |
// |----|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
// | Ex | à | á | â | ã | ä | å | æ | ç | è | é | ê | ë | ì | í | î | ï |
// |----|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
// | Fx | ð | ñ | ò | ó | ô | õ | ö | ÷ | ø | ù | ú | û | ü | ý | þ | ÿ |
// |--------------------------------------------------------------------|

// English part.
static const char FONT_EN_H5_V8_FIRST = 0x20;
static const char FONT_EN_H5_V8_LAST  = 0x7A;
static const PROGMEM uint8_t FONT_EN_H5_V8[92][5] = 
                                       {{0x00, 0x00, 0x00, 0x00, 0x00}, // sp
                                        {0x00, 0x00, 0x2f, 0x00, 0x00}, // !
                                        {0x00, 0x07, 0x00, 0x07, 0x00}, // "
                                        {0x14, 0x7f, 0x14, 0x7f, 0x14}, // #
                                        {0x24, 0x2a, 0x7f, 0x2a, 0x12}, // $
                                        {0x62, 0x64, 0x08, 0x13, 0x23}, // %
                                        {0x36, 0x49, 0x55, 0x22, 0x50}, // &
                                        {0x00, 0x05, 0x03, 0x00, 0x00}, // '
                                        {0x00, 0x1c, 0x22, 0x41, 0x00}, // (
                                        {0x00, 0x41, 0x22, 0x1c, 0x00}, // )
                                        {0x14, 0x08, 0x3E, 0x08, 0x14}, // *
                                        {0x08, 0x08, 0x3E, 0x08, 0x08}, // +
                                        {0x00, 0x00, 0xA0, 0x60, 0x00}, // ,
                                        {0x08, 0x08, 0x08, 0x08, 0x08}, // -
                                        {0x00, 0x60, 0x60, 0x00, 0x00}, // .
                                        {0x20, 0x10, 0x08, 0x04, 0x02}, // /
                                        {0x3E, 0x51, 0x49, 0x45, 0x3E}, // 0
                                        {0x00, 0x42, 0x7F, 0x40, 0x00}, // 1
                                        {0x42, 0x61, 0x51, 0x49, 0x46}, // 2
                                        {0x21, 0x41, 0x45, 0x4B, 0x31}, // 3
                                        {0x18, 0x14, 0x12, 0x7F, 0x10}, // 4
                                        {0x27, 0x45, 0x45, 0x45, 0x39}, // 5
                                        {0x3C, 0x4A, 0x49, 0x49, 0x30}, // 6
                                        {0x01, 0x71, 0x09, 0x05, 0x03}, // 7
                                        {0x36, 0x49, 0x49, 0x49, 0x36}, // 8
                                        {0x06, 0x49, 0x49, 0x29, 0x1E}, // 9
                                        {0x00, 0x36, 0x36, 0x00, 0x00}, // :
                                        {0x00, 0x56, 0x36, 0x00, 0x00}, // ;
                                        {0x08, 0x14, 0x22, 0x41, 0x00}, // <
                                        {0x14, 0x14, 0x14, 0x14, 0x14}, // =
                                        {0x00, 0x41, 0x22, 0x14, 0x08}, // >
                                        {0x02, 0x01, 0x51, 0x09, 0x06}, // ?
                                        {0x32, 0x49, 0x59, 0x51, 0x3E}, // @
                                        {0x7C, 0x12, 0x11, 0x12, 0x7C}, // A
                                        {0x7F, 0x49, 0x49, 0x49, 0x36}, // B
                                        {0x3E, 0x41, 0x41, 0x41, 0x22}, // C
                                        {0x7F, 0x41, 0x41, 0x22, 0x1C}, // D
                                        {0x7F, 0x49, 0x49, 0x49, 0x41}, // E
                                        {0x7F, 0x09, 0x09, 0x09, 0x01}, // F
                                        {0x3E, 0x41, 0x49, 0x49, 0x7A}, // G
                                        {0x7F, 0x08, 0x08, 0x08, 0x7F}, // H
                                        {0x00, 0x41, 0x7F, 0x41, 0x00}, // I
                                        {0x20, 0x40, 0x41, 0x3F, 0x01}, // J
                                        {0x7F, 0x08, 0x14, 0x22, 0x41}, // K
                                        {0x7F, 0x40, 0x40, 0x40, 0x40}, // L
                                        {0x7F, 0x02, 0x0C, 0x02, 0x7F}, // M
                                        {0x7F, 0x04, 0x08, 0x10, 0x7F}, // N
                                        {0x3E, 0x41, 0x41, 0x41, 0x3E}, // O
                                        {0x7F, 0x09, 0x09, 0x09, 0x06}, // P
                                        {0x3E, 0x41, 0x51, 0x21, 0x5E}, // Q
                                        {0x7F, 0x09, 0x19, 0x29, 0x46}, // R
                                        {0x46, 0x49, 0x49, 0x49, 0x31}, // S
                                        {0x01, 0x01, 0x7F, 0x01, 0x01}, // T
                                        {0x3F, 0x40, 0x40, 0x40, 0x3F}, // U
                                        {0x1F, 0x20, 0x40, 0x20, 0x1F}, // V
                                        {0x3F, 0x40, 0x38, 0x40, 0x3F}, // W
                                        {0x63, 0x14, 0x08, 0x14, 0x63}, // X
                                        {0x07, 0x08, 0x70, 0x08, 0x07}, // Y
                                        {0x61, 0x51, 0x49, 0x45, 0x43}, // Z
                                        {0x00, 0x7F, 0x41, 0x41, 0x00}, // [
                                        {0x55, 0x2A, 0x55, 0x2A, 0x55}, // 55
                                        {0x00, 0x41, 0x41, 0x7F, 0x00}, // ]
                                        {0x04, 0x02, 0x01, 0x02, 0x04}, // ^
                                        {0x40, 0x40, 0x40, 0x40, 0x40}, // _
                                        {0x00, 0x01, 0x02, 0x04, 0x00}, // '
                                        {0x20, 0x54, 0x54, 0x54, 0x78}, // a
                                        {0x7F, 0x48, 0x44, 0x44, 0x38}, // b
                                        {0x38, 0x44, 0x44, 0x44, 0x00}, // c
                                        {0x38, 0x44, 0x44, 0x48, 0x7F}, // d
                                        {0x38, 0x54, 0x54, 0x54, 0x18}, // e
                                        {0x08, 0x7E, 0x09, 0x01, 0x02}, // f
                                        {0x18, 0xA4, 0xA4, 0xA4, 0x7C}, // g
                                        {0x7F, 0x08, 0x04, 0x04, 0x78}, // h
                                        {0x00, 0x44, 0x7D, 0x40, 0x00}, // i
                                        {0x40, 0x80, 0x84, 0x7D, 0x00}, // j
                                        {0x7F, 0x10, 0x28, 0x44, 0x00}, // k
                                        {0x00, 0x41, 0x7F, 0x40, 0x00}, // l
                                        {0x7C, 0x04, 0x18, 0x04, 0x78}, // m
                                        {0x7C, 0x08, 0x04, 0x04, 0x78}, // n
                                        {0x38, 0x44, 0x44, 0x44, 0x38}, // o
                                        {0xFC, 0x24, 0x24, 0x24, 0x18}, // p
                                        {0x18, 0x24, 0x24, 0x18, 0xFC}, // q
                                        {0x7C, 0x08, 0x04, 0x04, 0x08}, // r
                                        {0x48, 0x54, 0x54, 0x54, 0x20}, // s
                                        {0x04, 0x3F, 0x44, 0x40, 0x20}, // t
                                        {0x3C, 0x40, 0x40, 0x20, 0x7C}, // u
                                        {0x1C, 0x20, 0x40, 0x20, 0x1C}, // v
                                        {0x3C, 0x40, 0x30, 0x40, 0x3C}, // w
                                        {0x44, 0x28, 0x10, 0x28, 0x44}, // x
                                        {0x1C, 0xA0, 0xA0, 0xA0, 0x7C}, // y
                                        {0x44, 0x64, 0x54, 0x4C, 0x44}, // z
                                        {0x14, 0x14, 0x14, 0x14, 0x14}};// lines


// Cyrillic part.
static const char FONT_CYR_H5_V8_FIRST = 0xC0;
static const char FONT_CYR_H5_V8_LAST  = 0xFF;
static const PROGMEM uint8_t FONT_CYR_H5_V8[64][5] = 
                                       {{0x7C, 0x12, 0x11, 0x12, 0x7C}, // À
                                        {0x7F, 0x49, 0x49, 0x49, 0x33}, // Á
                                        {0x7F, 0x49, 0x49, 0x49, 0x36}, // Â
                                        {0x7F, 0x01, 0x01, 0x01, 0x03}, // Ã
                                        {0x70, 0x29, 0x27, 0x21, 0x7F}, // Ä
                                        {0x7F, 0x49, 0x49, 0x49, 0x41}, // Å
                                        {0x77, 0x08, 0x7F, 0x08, 0x77}, // Æ
                                        {0x41, 0x49, 0x49, 0x49, 0x36}, // Ç
                                        {0x7F, 0x10, 0x08, 0x04, 0x7F}, // È
                                        {0x7C, 0x21, 0x12, 0x09, 0x7C}, // É
                                        {0x7F, 0x08, 0x14, 0x22, 0x41}, // Ê
                                        {0x20, 0x41, 0x3F, 0x01, 0x7F}, // Ë
                                        {0x7F, 0x02, 0x0C, 0x02, 0x7F}, // Ì
                                        {0x7F, 0x08, 0x08, 0x08, 0x7F}, // Í
                                        {0x3E, 0x41, 0x41, 0x41, 0x3E}, // Î
                                        {0x7F, 0x01, 0x01, 0x01, 0x7F}, // Ï
                                        {0x7F, 0x09, 0x09, 0x09, 0x06}, // Ð
                                        {0x3E, 0x41, 0x41, 0x41, 0x22}, // Ñ
                                        {0x01, 0x01, 0x7F, 0x01, 0x01}, // Ò
                                        {0x47, 0x28, 0x10, 0x08, 0x07}, // Ó
                                        {0x1C, 0x22, 0x7F, 0x22, 0x1C}, // Ô
                                        {0x63, 0x14, 0x08, 0x14, 0x63}, // Õ
                                        {0x7F, 0x40, 0x40, 0x40, 0xFF}, // Ö
                                        {0x07, 0x08, 0x08, 0x08, 0x7F}, // ×
                                        {0x7F, 0x40, 0x7F, 0x40, 0x7F}, // Ø
                                        {0x7F, 0x40, 0x7F, 0x40, 0xFF}, // Ù
                                        {0x01, 0x7F, 0x48, 0x48, 0x30}, // Ú
                                        {0x7F, 0x48, 0x30, 0x00, 0x7F}, // Û
                                        {0x7F, 0x48, 0x48, 0x30, 0x00}, // Ü
                                        {0x00, 0x41, 0x49, 0x49, 0x3E}, // Ý
                                        {0x7F, 0x08, 0x3E, 0x41, 0x3E}, // Þ
                                        {0x46, 0x29, 0x19, 0x09, 0x7F}, // ß
                                        {0x20, 0x54, 0x54, 0x54, 0x78}, // à
                                        {0x3C, 0x4A, 0x4A, 0x49, 0x31}, // á
                                        {0x7C, 0x54, 0x54, 0x28, 0x00}, // â
                                        {0x7C, 0x04, 0x04, 0x04, 0x0C}, // ã
                                        {0x70, 0x2A, 0x26, 0x22, 0x7E}, // ä
                                        {0x38, 0x54, 0x54, 0x54, 0x18}, // å
                                        {0x6C, 0x10, 0x7C, 0x10, 0x6C}, // æ
                                        {0x44, 0x44, 0x54, 0x54, 0x28}, // ç
                                        {0x7C, 0x20, 0x10, 0x08, 0x7C}, // è
                                        {0x78, 0x42, 0x24, 0x12, 0x78}, // é
                                        {0x7C, 0x10, 0x28, 0x44, 0x00}, // ê
                                        {0x20, 0x44, 0x3C, 0x04, 0x7C}, // ë
                                        {0x7C, 0x08, 0x10, 0x08, 0x7C}, // ì
                                        {0x7C, 0x10, 0x10, 0x10, 0x7C}, // í
                                        {0x38, 0x44, 0x44, 0x44, 0x38}, // î
                                        {0x7C, 0x04, 0x04, 0x04, 0x7C}, // ï
                                        {0xFC, 0x24, 0x24, 0x24, 0x18}, // ð
                                        {0x38, 0x44, 0x44, 0x44, 0x00}, // ñ
                                        {0x04, 0x04, 0x7C, 0x04, 0x04}, // ò
                                        {0x1C, 0xA0, 0xA0, 0xA0, 0x7C}, // ó
                                        {0x30, 0x48, 0xFE, 0x48, 0x30}, // ô
                                        {0x44, 0x28, 0x10, 0x28, 0x44}, // õ
                                        {0x7C, 0x40, 0x40, 0x40, 0xFC}, // ö
                                        {0x0C, 0x10, 0x10, 0x10, 0x7C}, // ÷
                                        {0x7C, 0x40, 0x7C, 0x40, 0x7C}, // ø
                                        {0x7C, 0x40, 0x7C, 0x40, 0xFC}, // ù
                                        {0x04, 0x7C, 0x50, 0x50, 0x20}, // ú
                                        {0x7C, 0x50, 0x20, 0x00, 0x7C}, // û
                                        {0x7C, 0x50, 0x50, 0x20, 0x00}, // ü
                                        {0x00, 0x44, 0x54, 0x54, 0x38}, // ý
                                        {0x7C, 0x10, 0x38, 0x44, 0x38}, // þ
                                        {0x00, 0x48, 0x34, 0x14, 0x7C}};// ÿ


c_font_h5_v8::c_font_h5_v8()
{

}

uint8_t c_font_h5_v8::get_char_column(char ch, uint8_t column)
{
    uint8_t tmp_ch = 0x00u;

    if (column < 5u)
    {
          //English symbol.
          if ((ch >= FONT_EN_H5_V8_FIRST) && (ch <= FONT_EN_H5_V8_LAST))
          {
               tmp_ch = pgm_read_byte_near(&FONT_EN_H5_V8[ch - FONT_EN_H5_V8_FIRST][column]);
          }
          //Cyrillic symbol.
          if ((ch >= FONT_CYR_H5_V8_FIRST) && (ch <= FONT_CYR_H5_V8_LAST))
          {        
               tmp_ch = pgm_read_byte_near(&FONT_CYR_H5_V8[ch - FONT_CYR_H5_V8_FIRST][column]);
          }
    }

    return tmp_ch;
}
