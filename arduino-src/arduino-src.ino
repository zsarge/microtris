#include <LiquidCrystal.h>
#include "display.hpp"

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
Display display = Display(&lcd);

const uint8_t offset = 6;
void setup() {
  Serial.begin(9600);  // open the serial port at 9600 bps:
  lcd.begin(16, 2);

  // design stored as bits
  bool myDesign[8][7] = {
    { 0, 0, 0, 0, 0, 0, 0 },
    { 0, 1, 0, 0, 0, 1, 0 },
    { 0, 1, 0, 0, 0, 1, 0 },
    { 0, 0, 0, 0, 0, 0, 0 },
    { 1, 0, 0, 0, 0, 0, 1 },
    { 0, 1, 0, 0, 0, 1, 0 },
    { 0, 0, 1, 1, 1, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0 },
  };

  for (int y = 0; y < 8; y++)
    for (int x = 0; x < 7; x++)
      if (myDesign[y][x])
        display.draw(x + offset, y);

  display.printToLcd();
}

void loop() {
  // design stored as coords
  uint8_t coords[4][2] = {
    { 1, 1 },
    { 1, 2 },
    { 5, 1 },
    { 5, 2 },
  };
  for (auto [x, y] : coords)
    display.toggle(x + offset, y);

  display.printToLcd();
  delay(1000);
}