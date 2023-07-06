#include "PG12032D.h"

/*
Simple sketch to test drawing of a user defined bitmap.
Modify the pins constants below to match your wiring.
*/

const int d0 = 9;
const int d1 = 8;
const int d2 = 7;
const int d3 = 6;
const int d4 = 5;
const int d5 = 4;
const int d6 = 3;
const int d7 = 2;

const int ao_cd = 10;
const int rw = 11;
const int e1 = 12;
const int e2 = 13;

PG12032D lcd(ao_cd, rw, e1, e2, d0, d1, d2, d3, d4, d5, d6, d7);

const uint8_t bitmap[] PROGMEM = {0xF0, 0x0F, 0x80,
                                  0x00, 0xFF, 0x01};

void setup() {
    Serial.begin(115200);
    lcd.begin();
    lcd.drawBitmap(0, 0, 3, 16, bitmap);
    lcd.refresh();
}

void loop() {

}
