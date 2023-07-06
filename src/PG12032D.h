#include "Arduino.h"
#include "Print.h"
#include "font.h"

const uint8_t LCD_OFF        = 0b10101110;
const uint8_t LCD_ON         = 0b10101111;
const uint8_t LCD_STARTLINE  = 0b11000000; // Or'd with the actual value
const uint8_t LCD_PAGE       = 0b10111000; // -"-
const uint8_t LCD_COLUMN     = 0b00000000; // -"-
const uint8_t LCD_NORMAL     = 0b10100000;
const uint8_t LCD_REVERSE    = 0b10100001;
const uint8_t LCD_STATIC_OFF = 0b10100100;
const uint8_t LCD_STATIC_ON  = 0b10100101;
const uint8_t LCD_DUTY_1_16  = 0b10101000;
const uint8_t LCD_DUTY_1_32  = 0b10101001;
const uint8_t LCD_RMW_START  = 0b11100000;
const uint8_t LCD_RMW_END    = 0b11101110;
const uint8_t LCD_RESET      = 0b11100010;

const uint8_t CHIP_PAGES   =  4;
const uint8_t CHIP_COLUMNS = 60;


class PG12032D : public Print
{
public:
    PG12032D(uint8_t ao, uint8_t rw, uint8_t e1, uint8_t e2,
            uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
            uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7
            );

    // High level functions for the user to interact with

    void begin();
    void clear();
    void drawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
    void setPixel(uint8_t x, uint8_t y);
    void clearPixel(uint8_t x, uint8_t y);
    void drawRectangle(uint8_t x, uint8_t y, uint8_t w, uint8_t h);
    void drawBox(uint8_t x, uint8_t y, uint8_t w, uint8_t h);
    void setCursor(uint8_t x, uint8_t y);
    void drawBitmap(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t bitmap[]);
    void drawBitmap(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const uint8_t bitmap[]);
    void refresh();

    // This implements a serial-ish printing

    virtual size_t write(uint8_t);
    using Print::write;

    // Medium level functions to send commands to the display

    void command(uint8_t value);
    void command(uint8_t chip, uint8_t value);
    void writeData(uint8_t chip, uint8_t value);
private:
    void _pulsePin(uint8_t chip);
    void _digitalWriteByteLSB(uint8_t hex);
    void _digitalWriteByteMSB(uint8_t hex);
    uint8_t _v_cursor_x;
    uint8_t _v_cursor_y;
    uint8_t _ao_pin;
    uint8_t _rw_pin;
    uint8_t _e1_pin;
    uint8_t _e2_pin;
    uint8_t _data_pins[8];
    uint8_t _buffer[120][4];
};
