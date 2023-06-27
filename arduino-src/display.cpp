#include "display.hpp"

Display::Display(LiquidCrystal* lcd) {
  this->lcd = lcd;
  for (int i = 0; i < board.charsWide * board.charsTall; i++) {
    for (int y = 0; y < character.pixelsTall; y++) {
      charBuffer[i][y] = 0;
    }
  }
}

void Display::printToSerial() {
  printLineToSerial();

  // print top row
  for (uint8_t y = 0; y < character.pixelsTall; y++) {  // for every pixelRow in first row
    for (uint8_t i = 0; i < 4; i++) {                   // print the columns
      printByte(charBuffer[i][y]);
    }
    Serial.println();
  }

  // print bottom row
  for (uint8_t y = 0; y < character.pixelsTall; y++) {  // for every pixelRow in first row
    for (uint8_t i = 4; i < 8; i++) {                   // print the columns
      printByte(charBuffer[i][y]);
    }
    Serial.println();
  }

  printLineToSerial();
}

void Display::printToLcd() {
  for (int i = 0; i < board.charsTall * board.charsWide; i++) {
    lcd->createChar(i, charBuffer[i]);
  }

  lcd->setCursor(0, 0);
  for (uint8_t i = 0; i < board.charsWide; i++) {
    lcd->write(i);
  }

  lcd->setCursor(0, 1);
  for (uint8_t i = 0; i < board.charsWide; i++) {
    lcd->write(i + 4);
  }
}

void Display::draw(uint8_t x, uint8_t y) {
  charBuffer[getCharacterBlock(x, y)][y % character.pixelsTall] |= getPattern(x);
}

void Display::erase(uint8_t x, uint8_t y) {
  charBuffer[getCharacterBlock(x, y)][y % character.pixelsTall] &= getPattern(x, 0b11101111);
}

void Display::set(uint8_t x, uint8_t y, bool state) {
  if (state) {
    draw(x, y);
  } else {
    erase(x, y);
  }
}

void Display::toggle(uint8_t x, uint8_t y) {
  charBuffer[getCharacterBlock(x, y)][y % character.pixelsTall] ^= getPattern(x);
}

bool Display::get(uint8_t x, uint8_t y) {
  return bitRead(
    charBuffer[getCharacterBlock(x, y)][y % character.pixelsTall],
    5 - (x % character.pixelsWide));
}

void Display::fill() {
  for (uint8_t i = 0; i < board.charsTall * board.charsWide; i++) {
    for (int8_t y = 0; y < character.pixelsTall; y++) {
      charBuffer[i][y] = 0b11111;
    }
  }
}

void Display::clear() {
  for (uint8_t i = 0; i < board.charsTall * board.charsWide; i++) {
    for (int8_t y = 0; y < character.pixelsTall; y++) {
      charBuffer[i][y] = 0;
    }
  }
}

void Display::printByte(byte val) {
  for (int j = 4; j >= 0; j--) {
    bool b = bitRead(val, j);
    Serial.print(b);
  }
}

byte Display::getPattern(uint8_t x) {
  return getPattern(x, 0b10000);
}

byte Display::getPattern(uint8_t x, uint8_t initialState) {
  return initialState >> x % character.pixelsWide;
}

void Display::printLineToSerial() {
  for (uint8_t x = 0; x < board.pixelsWide; x++) {
    Serial.print('-');
  }
  Serial.println();
}

uint8_t Display::getCharacterBlock(uint8_t x, uint8_t y) {
  if (y < 8) {
    return x / character.pixelsWide;
  } else {
    return (x / character.pixelsWide) + 4;
  }
}
