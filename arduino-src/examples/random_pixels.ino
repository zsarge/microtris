#include <LiquidCrystal.h>
#include "display.hpp"
/*
TODO:
- break classes into well formatted, seperate files
- generate custom characters on the fly
*/

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
Display display = Display(&lcd);

void setup() {
  Serial.begin(9600);  // open the serial port at 9600 bps:
  lcd.begin(16, 2);
  randomSeed(analogRead(0));
}

void loop() {
  for (uint8_t y = 0; y < display.board.pixelsTall; y++)
    for (uint8_t x = 0; x < display.board.pixelsWide; x++)
      if (random(0, 2) == 1)
        display.toggle(x, y);

  display.printToLcd();
  delay(1000);
}
