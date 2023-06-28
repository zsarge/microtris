#include <LiquidCrystal.h>
#include "display.hpp"
/*
TODO:
- break classes into well formatted, seperate files
- generate custom characters on the fly
*/

enum Direction : uint8_t {
  North,
  South,
  East,
  West
};

// there's a bit of an overhead to having a piece
// delegate to subclass via vtable, but it saves the
// headache of a piece not knowing how big it is.
class Piece {
protected:
  Direction direction;

public:
  void setDirection(Direction direction) {
    this->direction = direction;
  }
  void rotateClockwise() {
    switch (direction) {
      case North:
        direction = East;
        break;
      case East:
        direction = South;
        break;
      case South:
        direction = West;
        break;
      case West:
        direction = North;
        break;
    }
  }

  virtual ~Piece();
  virtual uint8_t getHeight();
  virtual uint8_t getWidth();
  virtual bool at(uint8_t, uint8_t);
};

Piece::~Piece() {}  // need to explicitly define this, to avoid linker errors
uint8_t Piece::getHeight() {
  return 0;  // should never get called
}
uint8_t Piece::getWidth() {
  return 0;  // should never get called
}
bool Piece::at(uint8_t x, uint8_t y) {
  return false;  // should never get called
}

class J : public Piece {
public:
  uint8_t getHeight() override {
    switch (direction) {
      case North:
      case South:
        return 3;
      case East:
      case West:
        return 2;
    }
  }
  uint8_t getWidth() override {
    switch (direction) {
      case North:
      case South:
        return 2;
      case East:
      case West:
        return 3;
    }
  }
  // is there a more efficent way to do this? probably
  bool at(uint8_t x, uint8_t y) override {
    if (x > getHeight() || y > getWidth()) return false;
    switch (direction) {
      case North:
        return (bool[3][2]){
          { 0, 1 },
          { 0, 1 },
          { 1, 1 },
        }[y][x];
      case East:
        return (bool[2][3]){
          { 1, 0, 0 },
          { 1, 1, 1 },
        }[y][x];
      case South:
        return (bool[3][2]){
          { 1, 1 },
          { 1, 0 },
          { 1, 0 },
        }[y][x];
      case West:
        return (bool[2][3]){
          { 1, 1, 1 },
          { 0, 0, 1 },
        }[y][x];
    }
  }
};

class L : public Piece {
public:
  uint8_t getHeight() override {
    switch (direction) {
      case North:
      case South:
        return 3;
      case East:
      case West:
        return 2;
    }
  }
  uint8_t getWidth() override {
    switch (direction) {
      case North:
      case South:
        return 2;
      case East:
      case West:
        return 3;
    }
  }

  bool at(uint8_t x, uint8_t y) override {
    if (x > getHeight() || y > getWidth()) return false;
    switch (direction) {
      case North:
        return (bool[3][2]){
          { 1, 0 },
          { 1, 0 },
          { 1, 1 },
        }[y][x];
      case East:
        return (bool[2][3]){
          { 1, 1, 1 },
          { 1, 0, 0 },
        }[y][x];
      case South:
        return (bool[3][2]){
          { 1, 1 },
          { 0, 1 },
          { 0, 1 },
        }[y][x];
      case West:
        return (bool[2][3]){
          { 0, 0, 1 },
          { 1, 1, 1 },
        }[y][x];
    }
  }
};


class O : public Piece {
public:
  uint8_t getHeight() override {
    return 2;
  }
  uint8_t getWidth() override {
    return 2;
  }
  bool at(uint8_t x, uint8_t y) override {
    if (x > getHeight() || y > getWidth()) return false;
    return true;
  }
};

class I : public Piece {
public:
  uint8_t getHeight() override {
    switch (direction) {
      case North:
      case South:
        return 4;
      case East:
      case West:
        return 1;
    }
  }
  uint8_t getWidth() override {
    switch (direction) {
      case North:
      case South:
        return 1;
      case East:
      case West:
        return 4;
    }
  }

  bool at(uint8_t x, uint8_t y) override {
    if (x > getHeight() || y > getWidth()) return false;
    return true;
  }
};

class S : public Piece {
public:
  uint8_t getHeight() override {
    switch (direction) {
      case North:
      case South:
        return 3;
      case East:
      case West:
        return 2;
    }
  }
  uint8_t getWidth() override {
    switch (direction) {
      case North:
      case South:
        return 2;
      case East:
      case West:
        return 3;
    }
  }

  bool at(uint8_t x, uint8_t y) override {
    if (x > getHeight() || y > getWidth()) return false;
    switch (direction) {
      case North:
        return (bool[3][2]){
          { 0, 1 },  // S
          { 1, 1 },
          { 1, 0 },
        }[y][x];
      case East:
        return (bool[2][3]){
          { 1, 1, 0 },
          { 0, 1, 1 },
        }[y][x];
      case South:
        return (bool[3][2]){
          { 1, 0 },  // S
          { 1, 1 },
          { 0, 1 },
        }[y][x];
      case West:
        return (bool[2][3]){
          { 0, 1, 1 },
          { 1, 1, 0 },
        }[y][x];
    }
  }
};

class Z : public Piece {
public:
  uint8_t getHeight() override {
    switch (direction) {
      case North:
      case South:
        return 3;
      case East:
      case West:
        return 2;
    }
  }
  uint8_t getWidth() override {
    switch (direction) {
      case North:
      case South:
        return 2;
      case East:
      case West:
        return 3;
    }
  }

  bool at(uint8_t x, uint8_t y) override {
    if (x > getHeight() || y > getWidth()) return false;
    switch (direction) {
      case North:
        return (bool[3][2]){
          { 0, 1 },  // Z
          { 1, 1 },
          { 1, 0 },
        }[y][x];
      case East:
        return (bool[2][3]){
          { 0, 1, 1 },
          { 1, 1, 0 },
        }[y][x];
      case South:
        return (bool[3][2]){
          { 0, 1 },  // S
          { 1, 1 },
          { 1, 0 },
        }[y][x];
      case West:
        return (bool[2][3]){
          { 1, 1, 0 },
          { 0, 1, 1 },
        }[y][x];
    }
  }
};


class Minitris {
private:
  Display* display;

  const static uint8_t height = 2 * 8;
  const static uint8_t width = 4 * 5;
  bool droppedBuffer[height][width];

  // piece variables
  Piece* piece;
  uint8_t x_offset;
  uint8_t y_offset;

  void resetToTop() {
    x_offset = width / 2;
    y_offset = 0;
  }

  void setNextPiece() {
    delete piece;
    piece = new J();
  }

  enum ButtonState : uint8_t {
    Up,
    Down,
    Left,
    Right,
    Select,
    None
  };

public:

  Minitris(const LiquidCrystal* lcd_ptr)
    : x_offset(0), y_offset(0) {
    this->display = new Display(lcd_ptr);

    for (uint8_t y = 0; y < height; y++)
      for (uint8_t x = 0; x < width; x++)
        this->droppedBuffer[y][x] = false;
    resetToTop();
    piece = new J();
  }

  ~Minitris() {
    delete this->display;
    delete piece;
  }

  // for use in scanning through a piece to see its state
  // after rotation
  bool at(uint8_t piece_x, uint8_t piece_y) {
    if (piece_x > 4 || piece_y > 4) return;
    // TODO: create instance variables:
    // - PieceName piece
    // - Direction direction
    // - uint8_T x_offset // in relation to the board
    // - uint8_T y_offset
  }

  ButtonState readButton() {
    int input = analogRead(0);
    if (input > 1000) return None;  // guard clause for most common result
    if (input < 50) return Right;
    if (input < 195) return Up;
    if (input < 380) return Down;
    if (input < 555) return Left;
    if (input < 790) return Select;
    return None;  // not sure how this would happen
  }

  // void rotateCounterClockwise() {
  //   switch (direction) {
  //     case Up:
  //     direction = Left
  //   }
  // }

  void moveLeft() {
    if (x_offset > 0)
      x_offset--;
  }

  void moveRight() {
    if (x_offset < width - piece->getWidth())
      x_offset++;
  }

  void moveDown() {
    if (y_offset < height - piece->getHeight())
      y_offset++;
  }

  void inputTick() {
    switch (readButton()) {
      case None: break;
      case Up:
        piece->rotateCounterClockwise();
        break;
      case Down:
        piece->rotateClockwise();
        break;
      case Left:
        moveLeft();
        break;
      case Right:
        moveRight();
        break;
      case Select:
        break;
    }
  }

  void gameTick() {
    moveDown();
  }
  /* draw() is in charge of rendering the piece,
   * and all of the dropped blocks, to the screen.
   */
  void draw() {
    Serial.print("Piece height: ");
    Serial.println(piece->getHeight());
    Serial.print("Piece Width: ");
    Serial.println(piece->getWidth());
    display->clear();

    drawPiece();

    // for (uint8_t piece = PieceName::I; piece != PieceName::S; piece++) {
    //   draw(piece, piece * 5, 0);
    // }
    // for (uint8_t piece = PieceName::S; piece != PieceName::Z; piece++) {
    //   draw(piece, (piece - PieceName::S) * 5, 16);
    // }
    // draw(PieceName::Z, 10, 16);

    display->printToLcd();
    // display->printToSerial();
  }



  void drawPiece() {
    for (uint8_t y = 0; y < piece->getHeight(); y++) {
      for (uint8_t x = 0; x < piece->getWidth(); x++) {
        display->set(x + x_offset, y + y_offset, piece->at(x, y));
      }
    }
  }
};

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
Minitris minitris = Minitris(&lcd);
// Display display(&lcd);

void setup() {
  Serial.begin(9600);  // open the serial port at 9600 bps:
  Serial.println("Serial port initalized...");
  lcd.begin(16, 2);

  // create wall
  lcd.setCursor(4, 0);
  lcd.write(255);
  lcd.setCursor(4, 1);
  lcd.write(255);

  // display.draw(5, 5);
  // display.printToLcd();

  minitris.draw();
}

void loop() {
  minitris.inputTick();
  minitris.gameTick();
  minitris.draw();
  delay(500);
}