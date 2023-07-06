#include "PG12032D.h"

/**
 * @brief Construct a new instance
 *
 * @details Will only prepare the data within the class. Put this in your global scope.
 * You will still have to call {@link begin} to set the pin modes and properly initialize the display.
 *
 * @param ao    the register select pin          (4)
 * @param rw    the read/write toggle pin        (5)
 * @param e1    chip enable for the first half   (6)
 * @param e2    chip enable for the second half  (7)
 * @param d0    data line N° 0                   (9)
 * @param d1    data line N° 1                  (10)
 * @param d2    data line N° 2                  (11)
 * @param d3    data line N° 3                  (12)
 * @param d4    data line N° 4                  (13)
 * @param d5    data line N° 5                  (14)
 * @param d6    data line N° 6                  (15)
 * @param d7    data line N° 7                  (16)
 *
 * @return returns a new instance
*/
PG12032D::PG12032D(uint8_t ao, uint8_t rw, uint8_t e1, uint8_t e2,
                uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
                uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) :
    _ao_pin(ao),
    _rw_pin(rw),
    _e1_pin(e1),
    _e2_pin(e2)
{
    _data_pins[0] = d0;
    _data_pins[1] = d1;
    _data_pins[2] = d2;
    _data_pins[3] = d3;
    _data_pins[4] = d4;
    _data_pins[5] = d5;
    _data_pins[6] = d6;
    _data_pins[7] = d7;
}


// High level functions
/**
 * @brief Initializes the display
 *
 * @details Sets the pin modes for all relevant pins,
 * sends a few initialization commands to both dispay controllers
 * and writes a clear buffer to the display.
 * Put this in your setup() scope.
 */
void PG12032D::begin() {
    pinMode(_ao_pin, OUTPUT);
    pinMode(_rw_pin, OUTPUT);
    pinMode(_e1_pin, OUTPUT);
    pinMode(_e2_pin, OUTPUT);

    for (int i = 0; i < 8; i++) {
        pinMode(_data_pins[i], OUTPUT);
    }

    command(LCD_RESET);
    delay(10);

    command(LCD_ON);
    command(LCD_NORMAL);
    command(LCD_PAGE | 0);
    command(LCD_COLUMN | 0);
    delay(10);
    refresh();
}

/**
 * @brief Clears the framebuffer
 *
 * @details Writes 0 to every location in the framebuffer.
 * You still have to call {@link refresh} for the buffer to take effect.
*/
void PG12032D::clear() {
    for (int i = 0; i < CHIP_PAGES; i++) {
        for (int j = 0; j < CHIP_COLUMNS * 2; j++) {
            _buffer[j][i] = 0;
        }
    }
}

/**
 * @brief Sets a single pixel to on
 *
 * @details Sets a single pixel in the framebuffer without affecting other data at that location.
 * You still have to call {@link refresh} for the buffer to take effect.
 *
 * @param x     the x coordinate of the pixel to be set
 * @param y     the y coordinate of the pixel to be set
 * @see clearPixel
*/
void PG12032D::setPixel(uint8_t x, uint8_t y) {
    _buffer[x][y / 8] |= 0b10000000 >> (y % 8);
}

/**
 * @brief Clears a single pixel
 *
 * @details Clears a single pixel i nthe framebuffer without affecting other data at that location.
 * You still have to call {@link refresh} for the buffer to take effect.
 *
 * @param x     the x coordinate of the pixel to be set
 * @param y     the y coordinate of the pixel to be set
 * @see setPixel
*/
void PG12032D::clearPixel(uint8_t x, uint8_t y) {
    _buffer[x][y / 8] &= ~(0b10000000 >> (y % 8));
}

/**
 * @brief Draws a line from one point to another
 *
 * @details Uses a derivation of Bresenham's line algorithm to draw a line to the framebuffer.
 * You still have to call {@link refresh} for the buffer to take effect.
 *
 * @param x0    the x coordinate of the first point
 * @param y0    the y coordinate of the first point
 * @param x1    the x coordinate of the second point
 * @param y1    the y coordinate of the second point
*/
void PG12032D::drawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
    int dx =  abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1;
    int err = dx + dy;
    int e2;

    while (true) {
        setPixel(x0,y0);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

/**
 * @brief Draws a filled rectangle anchored to a point
 *
 * @details Draws a rectangle with a width and height, anchored to a point into the framebuffer.
 * You still have to call {@link refresh} for the buffer to take effect.
 *
 * @param x     the x coordinate of the anchor point
 * @param y     the y coordinate of the anchor point
 * @param w     the width of the rectangle
 * @param h     the height of the rectangle
*/
void PG12032D::drawRectangle(uint8_t x, uint8_t y, uint8_t w, uint8_t h) {
    for (int i = y; i < y + h; i++) {
        drawLine(x, i, x + w, i);
    }
}

/**
 * @brief Draws an unfilled box anchored to a point
 *
 * @details Draws an unfilled box with a width and height, anchored to a point into the framebuffer
 * You still have to call {@link refresh} for the buffer to take effect.
 *
 * @param x     the x coordinate of the anchor point
 * @param y     the y coordinate of the anchor point
 * @param w     the width of the box
 * @param h     the height of the box
*/
void PG12032D::drawBox(uint8_t x, uint8_t y, uint8_t w, uint8_t h) {
    drawLine(x, y, x + w, y);
    drawLine(x, y + h, x + w, y + h);
    drawLine(x, y, x, y + h);
    drawLine(x + w, y, x + w, y + h);
}

/**
 * @brief Sets the virtual cursor
 *
 * @details Moves the virtual cursor to given location. This only affects the text printing.
 * Due to the framebuffer approach we have to keep track of where to put which charachter when printing.
 * You are not confined to any specific grid beyond the physical pixels.
 *
 * @see Print::print
 *
 * @param x     x coordinate of the new virtual cursor position
 * @param y     y coordinate of the new virtual cursor position
*/
void PG12032D::setCursor(uint8_t x, uint8_t y) {
    _v_cursor_x = x;
    _v_cursor_y = y;
}

/**
 * @brief Draws a bitmap to a location from SRAM
 *
 * @details Each byte in the bitmap is from MSB->up to LSB->down.
 * This function accesses a array pointer from SRAM and therefore,
 * can also print dynamically gnerated images.
 *
 * @param x         the x coordinate of the start location
 * @param y         the y coordinate of the start location
 * @param w         the width of the bitmap to be drawn
 * @param h         the height of the bitmap to be drawn
 * @param bitmap    a pointer to an array in SRAM
*/
void PG12032D::drawBitmap(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t bitmap[]) {
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            byte got_byte = bitmap[j/8*w + i];
            if (got_byte & (0b10000000 >> j % 8)) {
                setPixel(i + x, j + y);
            } else {
                clearPixel(i + x, j + y);
            }
        }
    }
}

/**
 * @brief Draws a bitmap to a location from PROGMEM
 *
 * @details Each byte in the bitmap is from MSB->up to LSB->down.
 * This function accesses a array pointer from PROGMEM and therefore,
 * can not draw dynamically generated or modified images.
 *
 * @param x         the x coordinate of the start location
 * @param y         the y coordinate of the start location
 * @param w         the width of the bitmap to be drawn
 * @param h         the height of the bitmap to be drawn
 * @param bitmap    a pointer to an array in PROGMEM
*/
void PG12032D::drawBitmap(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const uint8_t bitmap[]) {
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            byte got_byte = pgm_read_byte_near(bitmap + j/8*w + i);
            if (got_byte & (0b10000000 >> j % 8)) {
                setPixel(i + x, j + y);
            } else {
                clearPixel(i + x, j + y);
            }
        }
    }
}

/**
 * @brief Semi-internal function to facilitate Serial-esque printing
 *
 * @details The Print interface handles formatting and everything ugly,
 * this only gets the single chars and cares about properly writing the corresponding bitmap to the cursor location.
 *
 * @param value the char that is to be written
 * @return      wether the operation was successful or not, this always indicates success
*/
size_t PG12032D::write(uint8_t value) {
    for (int i = 0; i <8; i++) {
        byte got_char = pgm_read_byte_near(FONT + (value - CHAR_OFFSET) * 8 + i);
        for (int j = 0; j < 8; j++) {
            if (got_char & (1 << j)) {
                setPixel(_v_cursor_x + i, _v_cursor_y + j);
            } else {
                clearPixel(_v_cursor_x + i, _v_cursor_y + j);
            }
        }
    }
    _v_cursor_x += 8;
    return 1;
}

/**
 * @brief Writes the framebuffer to the display
 *
 * @details Whatever modifications have been made to th framebuffer by the draw funcions
 * get drawn to both display halves in "parallel".
*/
void PG12032D::refresh() {
    for (int i = 0; i < CHIP_PAGES; i++) {
        command(LCD_PAGE | i);
        command(LCD_COLUMN | 0);
        for (int j = 0; j < CHIP_COLUMNS; j++) {
            writeData(_e1_pin, _buffer[j][i]);
            writeData(_e2_pin, _buffer[j + CHIP_COLUMNS][i]);
        }
    }
}


// Medium level functions
/**
 * @brief Sends a command to both chips
 *
 * @details Calls the per-chip command function for each chip.
 *
 * @param value the command to be send to both chips
*/
void PG12032D::command(uint8_t value) {
    command(_e1_pin, value);
    command(_e2_pin, value);
}

/**
 * @brief Writes a command to a chip pin
 *
 * @details Sets the register select and rw pins accordingly,
 * writes out the command to the data bus with the least significant bit first,
 * then pulses the enable pin of the given chip
 *
 * @param chip  pin number of the target chip
 * @param value the command that is to be sent
*/
void PG12032D::command(uint8_t chip, uint8_t value) {
    digitalWrite(_ao_pin, LOW);
    digitalWrite(_rw_pin, LOW);
    _digitalWriteByteLSB(value);
    _pulsePin(chip);
}

/**
 * @brief Writes data to a chip pin
 *
 * @details Sets the register select and rw pins accordingly
 * writes out the data to the data bus with the most significant bit first,
 * then pulses the enable pin of the given chip
 *
 * @param chip  pin number of the target chip
 * @param value the data that is to be sent
*/
void PG12032D::writeData(uint8_t chip, uint8_t value) {
    digitalWrite(_ao_pin, HIGH);
    digitalWrite(_rw_pin, LOW);
    _digitalWriteByteMSB(value);
    _pulsePin(chip);
}


// Low level functions, not exposed
/**
 * @brief Pulses the enable pin with a specific timing
 *
 * @param chip  pin number of the target chip
*/
void PG12032D::_pulsePin(uint8_t chip) {
    digitalWrite(chip, LOW);
    delayMicroseconds(1);
    digitalWrite(chip, HIGH);
    delayMicroseconds(1);
    digitalWrite(chip, LOW);
    delayMicroseconds(100); // Process command
}

/**
 * @brief Writes a byte to the data bus lines (LSB)
 *
 * @details This is used by the command function because commands have to be in LSB format
 *
 * @param hex   the byte to be put out on the data lines
*/
void PG12032D::_digitalWriteByteLSB(uint8_t hex) {
    for (int i = 0; i < 8; i++) {
        digitalWrite(_data_pins[i], hex & (0b00000001 << i));
    }
}

/**
 * @brief Writes a byte to the data bus lines (MSB)
 *
 * @details This is used by the data function because data has to be in MSB format
 *
 * @param hex   the byte to be put out on the data lines
*/
void PG12032D::_digitalWriteByteMSB(uint8_t hex) {
    for (int i = 0; i < 8; i++) {
        digitalWrite(_data_pins[i], hex & (0b10000000 >> i));
    }
}
