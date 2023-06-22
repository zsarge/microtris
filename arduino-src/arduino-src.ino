#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);

  uint8_t approximations[] = {
    161,  // bottom left dot
    223,  // top right dot
    95,   // bar bottom
    91,   // bar left
    93,   // bar right
    204   // bar top and bar right
  };

  for (auto a : approximations)
    lcd.write(a);

  lcd.setCursor(0, 1);
  lcd.write(255);
}

void loop() {}
