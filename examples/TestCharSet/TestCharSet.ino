#include "PG12032D.h"
#include "Arduino.h"

/*
Simple sketch to test the look of the configured charset.
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

void setup() {
    Serial.begin(115200);
    lcd.begin();
}

void loop() {
    lcd.setCursor(0,0);
    lcd.print(" !\"#$%&'()*+,-./");
    lcd.setCursor(0, 8);
    lcd.print("0123456789:;<=>?");
    lcd.setCursor(0, 16);
    lcd.print("@ABCDEFGHIJKLMNO");
    lcd.setCursor(0, 24);
    lcd.print("PQRSTUVWXYZ[\\]^_");
    lcd.refresh();
    delay(5000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("`abcdefghijklmno");
    lcd.setCursor(0, 8);
    lcd.print("pqrstuvwxyz{|}~");
    lcd.setCursor(0, 16);
    lcd.print("Hello World!");
    lcd.setCursor(0, 24);
    lcd.print("From PG12032D");
    lcd.refresh();
    delay(5000);
    lcd.clear();
}
