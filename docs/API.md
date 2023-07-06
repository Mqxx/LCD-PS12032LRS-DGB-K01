---
title: PG12032D

---

# PG12032D

## Public Functions

|                | Name           |
| -------------- | -------------- |
| | **[PG12032D](#function-pg12032d)**(uint8_t ao, uint8_t rw, uint8_t e1, uint8_t e2, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7)<br>Construct a new instance.  |
| void | **[begin](#function-begin)**()<br>Initializes the display.  |
| void | **[clear](#function-clear)**()<br>Clears the framebuffer.  |
| void | **[drawLine](#function-drawline)**(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)<br>Draws a line from one point to another.  |
| void | **[setPixel](#function-setpixel)**(uint8_t x, uint8_t y)<br>Sets a single pixel to on.  |
| void | **[clearPixel](#function-clearpixel)**(uint8_t x, uint8_t y)<br>Clears a single pixel.  |
| void | **[drawRectangle](#function-drawrectangle)**(uint8_t x, uint8_t y, uint8_t w, uint8_t h)<br>Draws a filled rectangle anchored to a point.  |
| void | **[drawBox](#function-drawbox)**(uint8_t x, uint8_t y, uint8_t w, uint8_t h)<br>Draws an unfilled box anchored to a point.  |
| void | **[setCursor](#function-setcursor)**(uint8_t x, uint8_t y)<br>Sets the virtual cursor.  |
| void | **[drawBitmap](#function-drawbitmap)**(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t bitmap[])<br>Draws a bitmap to a location from SRAM.  |
| void | **[drawBitmap](#function-drawbitmap)**(uint8_t x, uint8_t y, uint8_t w, uint8_t h, const uint8_t bitmap[]) |
| void | **[refresh](#function-refresh)**()<br>Writes the framebuffer to the display.  |
| virtual size_t | **[write](#function-write)**(uint8_t value)<br>Semi-internal function to facilitate Serial-esque printing.  |
| void | **[command](#function-command)**(uint8_t value)<br>Sends a command to both chips.  |
| void | **[command](#function-command)**(uint8_t chip, uint8_t value)<br>Writes a command to a chip pin.  |
| void | **[writeData](#function-writedata)**(uint8_t chip, uint8_t value)<br>Writes data to a chip pin.  |

---
## function PG12032D

```cpp
PG12032D(
    uint8_t ao,
    uint8_t rw,
    uint8_t e1,
    uint8_t e2,
    uint8_t d0,
    uint8_t d1,
    uint8_t d2,
    uint8_t d3,
    uint8_t d4,
    uint8_t d5,
    uint8_t d6,
    uint8_t d7
)
```

Construct a new instance.

**Parameters**:

  * **ao** the register select pin (4)
  * **rw** the read/write toggle pin (5)
  * **e1** chip enable for the first half (6)
  * **e2** chip enable for the second half (7)
  * **d0** data line N° 0 (9)
  * **d1** data line N° 1 (10)
  * **d2** data line N° 2 (11)
  * **d3** data line N° 3 (12)
  * **d4** data line N° 4 (13)
  * **d5** data line N° 5 (14)
  * **d6** data line N° 6 (15)
  * **d7** data line N° 7 (16)


**Return**: returns a new instance

Will only prepare the data within the class. Put this in your global scope. You will still have to call [begin](#function-begin) to set the pin modes and properly initialize the display.

---
## function begin

```cpp
void begin()
```

Initializes the display.

Sets the pin modes for all relevant pins, sends a few initialization commands to both dispay controllers and writes a clear buffer to the display. Put this in your setup() scope.


---
## function clear

```cpp
void clear()
```

Clears the framebuffer.

Writes 0 to every location in the framebuffer. You still have to call [refresh](#function-refresh) for the buffer to take effect.


---
## function drawLine

```cpp
void drawLine(
    uint8_t x0,
    uint8_t y0,
    uint8_t x1,
    uint8_t y1drawRectangle
)
```

Draws a line from one point to another.

**Parameters**:

  * **x0** the x coordinate of the first point
  * **y0** the y coordinate of the first point
  * **x1** the x coordinate of the second point
  * **y1** the y coordinate of the second point


Uses a derivation of Bresenham's line algorithm to draw a line to the framebuffer. You still have to call [refresh](#function-refresh) for the buffer to take effect.


---
## function setPixel

```cpp
void setPixel(
    uint8_t x,
    uint8_t y
)
```

Sets a single pixel to on.

**Parameters**:

  * **x** the x coordinate of the pixel to be set
  * **y** the y coordinate of the pixel to be set


**See**: [clearPixel](#function-clearpixel)

Sets a single pixel in the framebuffer without affecting other data at that location. You still have to call [refresh](#function-refresh) for the buffer to take effect.


---
## function clearPixel

```cpp
void clearPixel(
    uint8_t x,
    uint8_t y
)
```

Clears a single pixel.

**Parameters**:

  * **x** the x coordinate of the pixel to be set
  * **y** the y coordinate of the pixel to be set


**See**: [setPixel](#function-setpixel)

Clears a single pixel i nthe framebuffer without affecting other data at that location. You still have to call [refresh](#function-refresh) for the buffer to take effect.


---
## function drawRectangle

```cpp
void drawRectangle(
    uint8_t x,
    uint8_t y,
    uint8_t w,
    uint8_t h
)
```

Draws a filled rectangle anchored to a point.

**Parameters**:

  * **x** the x coordinate of the anchor point
  * **y** the y coordinate of the anchor point
  * **w** the width of the rectangle
  * **h** the height of the rectangle


Draws a rectangle with a width and height, anchored to a point into the framebuffer. You still have to call [refresh](#function-refresh) for the buffer to take effect.


---
## function drawBox

```cpp
void drawBox(
    uint8_t x,
    uint8_t y,
    uint8_t w,
    uint8_t h
)
```

Draws an unfilled box anchored to a point.

**Parameters**:

  * **x** the x coordinate of the anchor point
  * **y** the y coordinate of the anchor point
  * **w** the width of the box
  * **h** the height of the box


Draws an unfilled box with a width and height, anchored to a point into the framebuffer You still have to call [refresh](#function-refresh) for the buffer to take effect.


---
## function setCursor

```cpp
void setCursor(
    uint8_t x,
    uint8_t y
)
```

Sets the virtual cursor.

**Parameters**:

  * **x** x coordinate of the new virtual cursor position
  * **y** y coordinate of the new virtual cursor position


**See**: Print::print

Moves the virtual cursor to given location. This only affects the text printing. Due to the framebuffer approach we have to keep track of where to put which charachter when printing. You are not confined to any specific grid beyond the physical pixels.


---
## function drawBitmap

```cpp
void drawBitmap(
    uint8_t x,
    uint8_t y,
    uint8_t w,
    uint8_t h,
    uint8_t bitmap[]
)
```

Draws a bitmap to a location from SRAM.

**Parameters**:

  * **x** the x coordinate of the start location
  * **y** the y coordinate of the start location
  * **w** the width of the bitmap to be drawn
  * **h** the height of the bitmap to be drawn
  * **bitmap** a pointer to an array in SRAM
  * **x** the x coordinate of the start location
  * **y** the y coordinate of the start location
  * **w** the width of the bitmap to be drawn
  * **h** the height of the bitmap to be drawn
  * **bitmap** a pointer to an array in PROGMEM


Draws a bitmap to a location from PROGMEM.

Each byte in the bitmap is from MSB->up to LSB->down. This function accesses a array pointer from SRAM and therefore, can also print dynamically gnerated images.

Each byte in the bitmap is from MSB->up to LSB->down. This function accesses a array pointer from PROGMEM and therefore, can not draw dynamically generated or modified images.


---
## function drawBitmap

```cpp
void drawBitmap(
    uint8_t x,
    uint8_t y,
    uint8_t w,
    uint8_t h,
    const uint8_t bitmap[]
)
```


---
## function refresh

```cpp
void refresh()
```

Writes the framebuffer to the display.

Whatever modifications have been made to th framebuffer by the draw funcions get drawn to both display halves in "parallel".


---
## function write

```cpp
virtual size_t write(
    uint8_t value
)
```

Semi-internal function to facilitate Serial-esque printing.

**Parameters**:

  * **value** the char that is to be written


**Return**: wether the operation was successful or not, this always indicates success

The Print interface handles formatting and everything ugly, this only gets the single chars and cares about properly writing the corresponding bitmap to the cursor location.


---
## function command

```cpp
void command(
    uint8_t value
)
```

Sends a command to both chips.

**Parameters**:

  * **value** the command to be send to both chips


Calls the per-chip command function for each chip.


---
## function command

```cpp
void command(
    uint8_t chip,
    uint8_t value
)
```

Writes a command to a chip pin.

**Parameters**:

  * **chip** pin number of the target chip
  * **value** the command that is to be sent


Sets the register select and rw pins accordingly, writes out the command to the data bus with the least significant bit first, then pulses the enable pin of the given chip


---
## function writeData

```cpp
void writeData(
    uint8_t chip,
    uint8_t value
)
```

Writes data to a chip pin.

**Parameters**:

  * **chip** pin number of the target chip
  * **value** the data that is to be sent


Sets the register select and rw pins accordingly writes out the data to the data bus with the most significant bit first, then pulses the enable pin of the given chip


-------------------------------

Updated on 2023-07-06
