#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

byte customChar[8] = {
  0b00000,
  0b01010,
  0b01010,
  0b00000,
  0b10001,
  0b01110,
  0b00000,
  0b00000
};

void setup() {
  lcd.createChar(0, customChar);
  lcd.begin(16, 2);  // start the library
  lcd.setCursor(0, 0);
  lcd.print("Hello, World!");  // print a simple message
  lcd.setCursor(0, 1);
  lcd.write((uint8_t)0);
}

void loop() {}
