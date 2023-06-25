#include <LiquidCrystal.h>

/*
TODO:
- break classes into well formatted, seperate files
- generate custom characters on the fly
*/

class Display {
private:
  byte charBuffer[8][8];
public:
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
    for (int i = 0; i < board.charsTall * board.charsWide; i++) {
      lcd.createChar(i, charBuffer[i]);
    }

    lcd.setCursor(0, 0);
    for (uint8_t i = 0; i < board.charsWide; i++) {
      lcd.write(i);
    }

    lcd.setCursor(0, 1);
    for (uint8_t i = 0; i < board.charsWide; i++) {
      lcd.write(i + 3);
    }
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

  void toggle(uint8_t x, uint8_t y) {
    charBuffer[getCharacterBlock(x, y)][y % character.pixelsTall] ^= getPattern(x);
  }

  void fill() {
    for (uint8_t i = 0; i < board.charsTall * board.charsWide; i++) {
      for (int8_t y = 0; y < character.pixelsTall; y++) {
        charBuffer[i][y] = 0b11111;
      }
    }
  }

  void clear() {
    for (uint8_t i = 0; i < board.charsTall * board.charsWide; i++) {
      for (int8_t y = 0; y < character.pixelsTall; y++) {
        charBuffer[i][y] = 0;
      }
    }
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
    return initialState >> x % character.pixelsWide;
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

  display.fill();
  for (uint8_t y = 0; y < display.board.pixelsTall; y++)
    for (uint8_t x = 0; x < display.board.pixelsWide; x++)
      if (x % 2 == 0 || y % 2 == 0)
        display.erase(x, y);

  Serial.println("Serial Port Initalized...");
  display.print_to_serial();
  display.print_to_lcd(lcd);
}

void loop() {
  display.toggle(10, 10);
  display.print_to_lcd(lcd);
  delay(1000);
}
