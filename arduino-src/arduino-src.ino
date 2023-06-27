#include <LiquidCrystal.h>
#include "display.hpp"
/*
TODO:
- break classes into well formatted, seperate files
- generate custom characters on the fly
*/

enum Direction : uint8_t {
  Up,
  Down,
  Left,
  Right
};

enum PieceName : uint8_t {
  I = 0,
  J,
  L,
  O,
  S,
  T,
  Z
};

// TODO: optimize into bits of bytes
const bool pieces[7][4][3] = {
  {
    { 0, 1, 0 },  // I
    { 0, 1, 0 },
    { 0, 1, 0 },
    { 0, 1, 0 },
  },
  {
    { 0, 1, 0 },  // J
    { 0, 1, 0 },
    { 0, 1, 0 },
    { 1, 1, 0 },
  },
  {
    { 1, 0, 0 },  // L
    { 1, 0, 0 },
    { 1, 0, 0 },
    { 1, 1, 0 },
  },
  {
    { 1, 1, 0 },  // O
    { 1, 1, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 },
  },
  {
    { 0, 1, 0 },  // S
    { 1, 1, 0 },
    { 1, 0, 0 },
    { 0, 0, 0 },
  },
  {
    { 0, 1, 0 },  // T
    { 1, 1, 1 },
    { 0, 0, 0 },
    { 0, 0, 0 },
  },
  {
    { 1, 0, 0 },  // Z
    { 1, 1, 0 },
    { 0, 1, 0 },
    { 0, 0, 0 },
  },
};

class Minitris {
private:
  Display* display;

public:

  Minitris(const LiquidCrystal* lcd_ptr) {
    this->display = new Display(lcd_ptr);
  }
  ~Minitris() {
    delete this->display;
  }

  void draw() {
    for (uint8_t piece = PieceName::I; piece != PieceName::S; piece++) {
      draw(piece, piece * 5, 0);
    }
    for (uint8_t piece = PieceName::S; piece != PieceName::Z; piece++) {
      draw(piece, (piece - PieceName::S) * 5, 16);
    }
    draw(PieceName::Z, 10, 16);

    display->printToLcd();
    display->printToSerial();
  }

  void draw(PieceName piece, uint8_t x_offset, uint8_t y_offset) {
    uint8_t width = 3;
    uint8_t height = 4;

    for (uint8_t y = 0; y < height; y++) {
      for (uint8_t x = 0; x < width; x++) {
        display->set(x + x_offset, y + y_offset, pieces[piece][y][x]);
      }
    }
  }

  void tick() {
  }
};

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
Minitris minitris = Minitris(&lcd);
// Display display(&lcd);

void setup() {
  Serial.begin(9600);  // open the serial port at 9600 bps:
  lcd.begin(16, 2);

  // display.draw(5, 5);
  // display.printToLcd();

  minitris.draw();
}

void loop() {}

// LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
// Display display(&lcd);

// void setup() {
//   Serial.begin(9600);  // open the serial port at 9600 bps:
//   lcd.begin(16, 2);
//   randomSeed(analogRead(0));
// }

// void loop() {
//   display.draw(1, 1);

//   display.printToLcd();
//   delay(1000);
// }