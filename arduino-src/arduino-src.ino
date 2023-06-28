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

  void rotateCounterClockwise() {
    switch (direction) {
      case North:
        direction = West;
        break;
      case West:
        direction = South;
        break;
      case South:
        direction = East;
        break;
      case East:
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
  switch (direction) {
    case North:
    case South:
      return 3;
    case East:
    case West:
      return 2;
  }
}
uint8_t Piece::getWidth() {
  switch (direction) {
    case North:
    case South:
      return 2;
    case East:
    case West:
      return 3;
  }
}
bool Piece::at(uint8_t x, uint8_t y) {
  return false;  // should never get called
}

class J : public Piece {
public:
  // is there a more efficent way to do this? probably
  bool at(uint8_t x, uint8_t y) override {
    if (x > getWidth() || y > getHeight()) return false;
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
  bool at(uint8_t x, uint8_t y) override {
    if (x > getWidth() || y > getHeight()) return false;
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

class T : public Piece {
public:
  bool at(uint8_t x, uint8_t y) override {
    if (x > getWidth() || y > getHeight()) return false;
    switch (direction) {
      case North:
        return (bool[3][2]){
          { 1, 0 },
          { 1, 1 },
          { 1, 0 },
        }[y][x];
      case East:
        return (bool[2][3]){
          { 1, 1, 1 },
          { 0, 1, 0 },
        }[y][x];
      case South:
        return (bool[3][2]){
          { 0, 1 },
          { 1, 1 },
          { 0, 1 },
        }[y][x];
      case West:
        return (bool[2][3]){
          { 0, 1, 0 },
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
    if (x > getWidth() || y > getHeight()) return false;
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
    if (x > getWidth() || y > getHeight()) return false;
    return true;
  }
};

class S : public Piece {
public:
  bool at(uint8_t x, uint8_t y) override {
    if (x > getWidth() || y > getHeight()) return false;
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
  bool at(uint8_t x, uint8_t y) override {
    if (x > getWidth() || y > getHeight()) return false;
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
          { 0, 1 },  // Z
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

  // A minitris display is a sideways Display.
  // That is:
  // display->board.pixelsTall == width && display->board.pixelsWide == height
  const static uint8_t height = 4 * 5;
  const static uint8_t width = 2 * 8;
  bool droppedBuffer[height][width];

  // piece variables
  Piece* piece;
  uint8_t x_offset;
  uint8_t y_offset;

  void resetToTop() {
    x_offset = width / 2;
    y_offset = 0;
    piece->setDirection(North);
  }

  void setNextPiece() {
    delete piece;
    switch (random(7)) {
      case 0:
        piece = new I();
        break;
      case 1:
        piece = new O();
        break;
      case 2:
        piece = new T();
        break;
      case 3:
        piece = new S();
        break;
      case 4:
        piece = new Z();
        break;
      case 5:
        piece = new J();
        break;
      case 6:
        piece = new L();
        break;
    }
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

    piece = new I();
    setNextPiece();
    resetToTop();
  }

  ~Minitris() {
    delete this->display;
    delete piece;
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


  void moveLeft() {
    if (x_offset <= 0) return;

    for (uint8_t y = 0; y < piece->getHeight(); y++) {
      for (uint8_t x = 0; x < piece->getWidth(); x++) {
        if (
          piece->at(x, y) && droppedBuffer[y + y_offset][x + x_offset - 1]  // there is a piece to the left
        ) {
          return;
        }
      }
    }

    x_offset--;
  }

  void moveRight() {
    if (x_offset >= width - piece->getWidth()) return;

    for (uint8_t y = 0; y < piece->getHeight(); y++) {
      for (uint8_t x = 0; x < piece->getWidth(); x++) {
        if (
          piece->at(x, y) && droppedBuffer[y + y_offset][x + x_offset + 1]  // there is a piece to the left
        ) {
          return;
        }
      }
    }

    x_offset++;
  }

  void moveDown() {
    if (y_offset < height - piece->getHeight())
      y_offset++;
  }

  void inputTick() {
    static ButtonState lastButtonState = None;
    ButtonState currentState = readButton();
    switch (currentState) {
      case None: break;
      case Up:
        moveLeft();
        break;
      case Down:
        moveRight();
        break;
      case Left:
        piece->rotateClockwise();
        break;
      case Right:
        piece->rotateCounterClockwise();
        break;
      case Select:
        if (lastButtonState != Select)
          dropPiece();
        break;
    }
    lastButtonState = currentState;
  }

  void reset() {
    placePiece();
    resetToTop();
    setNextPiece();
    draw();
    if (pieceIsStuck()) {
      loseGame();
    }
  }

  void gameTick() {
    if (pieceIsStuck()) {
      reset();
    } else {
      moveDown();
    }
    clearFullLines();

    // todo: check for clear lines?
  }

  bool pieceIsStuck() {
    // piece intersects bottom
    if (y_offset >= height - piece->getHeight()) {
      Serial.println("Piece is stuck!");
      return true;
    }
    // piece intersects dropped pieces
    for (uint8_t y = 0; y < piece->getHeight(); y++) {
      for (uint8_t x = 0; x < piece->getWidth(); x++) {
        if (
          (piece->at(x, y) && droppedBuffer[y + y_offset + 1][x + x_offset]) ||  // piece below
          (piece->at(x, y) && droppedBuffer[y + y_offset][x + x_offset])         // piece inside :(
        ) {
          return true;
        }
      }
    }
    return false;
  }

  bool lineIsFull(uint8_t line) {
    for (uint8_t x = 0; x < width; x++) {
      if (!droppedBuffer[line][x]) return false;
    }
    Serial.print(line);
    Serial.println(" line is full");
    return true;
  }

  void moveBoardDown(uint8_t line) {
    for (uint8_t y = line; y > 0; y--) {
      for (uint8_t x = 0; x < width; x++) {
        // y-1 is up 1 row from the starting line
        droppedBuffer[y][x] = droppedBuffer[y - 1][x];
      }
    }
  }

  void clearFullLines() {
    // start at bottom row
    // note (0,0) is top left
    for (uint8_t y = height - 1; y > 0; y--) {
      if (lineIsFull(y)) {
        // clear line
        for (uint8_t x = 0; x < width; x++) {
          droppedBuffer[y][x] = false;
        }

        // move everything else down 1 row
        moveBoardDown(y);
      }
    }
  }

  void loseGame() {
    this->display->lcd->setCursor(6, 0);
    this->display->lcd->print("You Lose!");
    this->display->lcd->setCursor(6, 1);
    this->display->lcd->print("Score: ?");
    delay(5000);
    this->display->lcd->clear();
    this->display->lcd->setCursor(4, 0);
    this->display->lcd->write(255);
    this->display->lcd->setCursor(4, 1);
    this->display->lcd->write(255);
    for (uint8_t y = 0; y < height; y++)
      for (uint8_t x = 0; x < width; x++)
        this->droppedBuffer[y][x] = false;
  }

  void placePiece() {
    for (uint8_t y = 0; y < piece->getHeight(); y++) {
      for (uint8_t x = 0; x < piece->getWidth(); x++) {
        if (piece->at(x, y)) {
          droppedBuffer[y + y_offset][x + x_offset] = true;
        }
      }
    }
  }

  void dropPiece() {
    while (!pieceIsStuck()) {
      moveDown();
    }
    reset();
  }

  /* draw() is in charge of rendering the piece,
   * and all of the dropped blocks, to the screen.
   */
  void draw() {
    display->clear();

    drawPiece();
    drawGameBoard();

    display->printToLcd();
    // display->printToSerial();
  }

  void drawGameBoard() {
    // assume game board is same size as display, just rotated 90 degrees
    for (uint8_t y = 0; y < height; y++) {
      for (uint8_t x = 0; x < width; x++) {
        if (droppedBuffer[y][x]) {
          display->draw(y, x);
        }
      }
    }
  }

  void drawPiece() {
    for (uint8_t y = 0; y < piece->getHeight(); y++) {
      for (uint8_t x = 0; x < piece->getWidth(); x++) {
        if (piece->at(x, y)) {
          display->draw(y + y_offset, x + x_offset);
        }
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
  randomSeed(analogRead(0));

  // create wall
  lcd.setCursor(4, 0);
  lcd.write(255);
  lcd.setCursor(4, 1);
  lcd.write(255);

  // display.draw(5, 5);
  // display.printToLcd();

  minitris.draw();
}

int tickTimes = 0;
void loop() {
  minitris.inputTick();
  if (tickTimes % 10 == 0)
    minitris.gameTick();
  minitris.draw();
  delay(100);
  tickTimes++;
}