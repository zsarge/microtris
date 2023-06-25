#include <LiquidCrystal.h>

/*
TODO:
- break classes into well formatted, seperate files
- generate custom characters on the fly
*/

class Display {
private:
  byte charBuffer[8][8];
  struct {
    uint8_t pixelsWide;
    uint8_t pixelsTall;
  } character = { 5, 8 };
  struct {
    uint8_t charsWide;
    uint8_t charsTall;
    uint8_t pixelsWide;
    uint8_t pixelsTall;
  } board = { 4, 2, 4 * 5, 2 * 8 };

public:
  uint8_t getCharacterBlock(uint8_t x, uint8_t y) {
    if (y < 8) {
      return x / character.pixelsWide;
    } else {
      return (x / character.pixelsWide) + 3;
    }
  }

  Display() {
    for (int i = 0; i < board.charsWide * board.charsTall; i++) {
      for (int y = 0; y < character.pixelsTall; y++) {
        charBuffer[i][y] = 0;
      }
    }
  }


  void print_to_serial() {
    print_line_to_serial();

    // print top row
    for (uint8_t y = 0; y < character.pixelsTall; y++) {  // for every pixelRow in first row
      for (uint8_t i = 0; i < 4; i++) {                   // print the columns
        printByte(charBuffer[i][y]);
      }
      Serial.println();
    }
    // print bottom row
    for (uint8_t y = 0; y < character.pixelsTall; y++) {  // for every pixelRow in first row
      for (uint8_t i = 0; i < 4; i++) {                   // print the columns
        printByte(charBuffer[i + 3][y]);
      }
      Serial.println();
    }

    print_line_to_serial();
  }

  // TODO: Fix naming conventions
  void print_to_lcd(LiquidCrystal& lcd) {
  }

  byte get(uint8_t x, uint8_t y) {
    return 1;
  }

  void draw(uint8_t x, uint8_t y) {
    charBuffer[getCharacterBlock(x, y)][y % character.pixelsTall] |= getPattern(x);
  }

  void erase(uint8_t x, uint8_t y) {
    charBuffer[getCharacterBlock(x, y)][y % character.pixelsTall] &= getPattern(x, 0b11101111);
  }

private:
  void printByte(byte val) {
    for (int j = 4; j >= 0; j--) {
      bool b = bitRead(val, j);
      Serial.print(b);
    }
  }

  byte getPattern(uint8_t x) {
    return getPattern(x, 0b10000);
  }

  byte getPattern(uint8_t x, uint8_t initialState) {
    uint8_t pattern = initialState;
    for (uint8_t i = 0; i < x % character.pixelsWide; i++) {
      pattern = pattern >> 1;
    }
    return pattern;
  }

  void print_line_to_serial() {
    for (uint8_t x = 0; x < board.pixelsWide; x++) {
      Serial.print('-');
    }
    Serial.println();
  }
};

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
Display display = Display();

void setup() {
  Serial.begin(9600);  // open the serial port at 9600 bps:
  lcd.begin(16, 2);
  lcd.clear();

  for (uint8_t y = 0; y < 8; y++)
    for (uint8_t x = 0; x < 8; x++)
      display.draw(x, y);

  display.erase(7, 7);

  Serial.println("Serial Port Initalized...");
  display.print_to_serial();
  // display.print_to_lcd(lcd);
}

void loop() {}
