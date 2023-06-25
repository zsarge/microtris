#ifndef HD_DISPLAY
#define HD_DISPLAY

#include <LiquidCrystal.h>
#include <Arduino.h>

class Display {
public:
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

  Display(LiquidCrystal* lcd);

  void printToSerial();
  void printToLcd();

  bool get(uint8_t x, uint8_t y);
  void draw(uint8_t x, uint8_t y);
  void erase(uint8_t x, uint8_t y);
  void toggle(uint8_t x, uint8_t y);
  void fill();
  void clear();

private:
  LiquidCrystal* lcd;
  uint8_t getCharacterBlock(uint8_t x, uint8_t y);
  void printByte(byte val);
  byte getPattern(uint8_t x);
  byte getPattern(uint8_t x, uint8_t initialState);
  void printLineToSerial();
};
#endif