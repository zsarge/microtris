#include <LiquidCrystal.h>



class Display {
private:
  uint8_t** buffer;
  uint8_t rows;
  uint8_t columns;
public:
  Display(uint8_t rows, uint8_t columns) {
    // allocate memory
    this->rows = rows;
    this->columns = columns;

    buffer = new uint8_t*[columns];
    for (int y = 0; y < columns; y++) {
      buffer[y] = new uint8_t[rows];
      // initialize values
      for (int x = 0; x < rows; x++) {
        buffer[y][x] = 0;
      }
    }
  }
  ~Display() {
    // handle cleanup
    for (int i = 0; i < rows; i++) {
      delete[] buffer[i];
    }
    delete[] buffer;
  }

  void print_to_serial() {
    Serial.println("printing to Serial");
    print_line_to_serial();
    for (uint8_t y = 0; y < columns; y++) {
      for (uint8_t x = 0; x < rows; x++) {
        Serial.print(buffer[y][x]);
      }
      Serial.println();
    }
    print_line_to_serial();
  }
private:
  void print_line_to_serial() {
    for (uint8_t x = 0; x < rows; x++) {
      Serial.print('-');
    }
    Serial.println();
  }
};

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
Display display(16 * 4, 2 * 4);

void setup() {
  Serial.begin(9600);  // open the serial port at 9600 bps:
  lcd.begin(16, 2);
  lcd.setCursor(0, 1);
  lcd.write(255);

  Serial.println("Serial Port Initalized...");
  display.print_to_serial();
}

void loop() {}
