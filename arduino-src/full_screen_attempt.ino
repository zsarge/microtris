// #include <LiquidCrystal.h>

// #define NUM_CHARS 16

// /*
// TODO:
// - break classes into well formatted, seperate files
// - generate custom characters on the fly
// */

// class CustomCharacterManager {
//   // private:
// public:
//   const uint8_t customCharacterLimit = 8;
//   bool storedOnBoard[customCharacterLimit];
//   int customCharacters;
//   struct {
//     bool can_be_approximated;
//     uint8_t character_approximation;
//     bool is_stored;
//     uint8_t stored_location;
//   } characters[NUM_CHARS];

//   uint8_t combine(uint8_t a, uint8_t b, uint8_t c, uint8_t d) {
//     uint8_t combined = 0;
//     combined |= (a << 3);
//     combined |= (b << 2);
//     combined |= (c << 1);
//     combined |= d;
//     return combined;
//   }

//   CustomCharacterManager() {
//     customCharacters = 0;
//     for (uint8_t i = 0; i < customCharacterLimit; i++) {
//       storedOnBoard[i] = false;
//     }
//     for (uint8_t i = 0; i < NUM_CHARS; i++) {
//       characters[i] = { false, 0, false, 0 };
//     }
//     // 8 characters can be approximated, in case they can't be set as custom characters
//     characters[0b0000] = { true, 32, false, 0 };
//     characters[0b0010] = { true, 161, false, 0 };
//     characters[0b1000] = { true, 223, false, 0 };
//     characters[0b0011] = { true, 95, false, 0 };
//     characters[0b1010] = { true, 91, false, 0 };
//     characters[0b0101] = { true, 93, false, 0 };
//     characters[0b1101] = { true, 204, false, 0 };
//     characters[0b1111] = { true, 255, false, 0 };
//   }


//   uint8_t getCode(uint8_t a, uint8_t b, uint8_t c, uint8_t d) {
//     if (!(a & b & c & d)) return 32;  // handle most common case early
//     if (a & b & c & d) return 255;
//     uint8_t charIndex = combine(a, b, c, d);

//     if (customCharacters < customCharacterLimit) {
//       if (characters[charIndex].is_stored) {
//         return characters[charIndex].stored_location;
//       } else {
//         uint8_t i = 0;
//         while (i < customCharacterLimit && !storedOnBoard[i]) {
//           i++;
//         }
//         lcd.createChar(i, design(a, b, c, d));
//         characters[charIndex].stored_location = i;
//       }
//     } else {
//       // todo: handle reallocation
//       return characters[charIndex].character_approximation;
//     }
//   }
// };

// class Display {
// private:
//   uint8_t** buffer;
//   CustomCharacterManager manager;
// public:
//   uint8_t rows;
//   uint8_t columns;

//   Display(uint8_t columns, uint8_t rows) {
//     // allocate memory
//     this->rows = rows;
//     this->columns = columns;
//     this->manager = CustomCharacterManager();

//     buffer = new uint8_t*[rows];
//     for (int y = 0; y < rows; y++) {
//       buffer[y] = new uint8_t[columns];
//       // initialize values
//       for (int x = 0; x < columns; x++) {
//         buffer[y][x] = 0;
//       }
//     }
//   }
//   ~Display() {
//     // handle cleanup
//     for (int x = 0; x < rows; x++) {
//       delete[] buffer[x];
//     }
//     delete[] buffer;
//   }

//   void print_to_serial() {
//     print_line_to_serial();
//     for (uint8_t y = 0; y < rows; y++) {
//       for (uint8_t x = 0; x < columns; x++) {
//         Serial.print(buffer[y][x]);
//       }
//       Serial.println();
//     }
//     print_line_to_serial();
//   }

//   // TODO: Fix naming conventions
//   void print_to_lcd(LiquidCrystal& lcd) {
//     for (uint8_t y = 0; y < rows; y += 2) {
//       lcd.setCursor(0, y / 2);
//       for (uint8_t x = 0; x < columns; x += 2) {
//         lcd.write(manager.getCode(buffer[y][x], buffer[y][x + 1], buffer[y + 1][x], buffer[y + 1][x + 1]));
//       }
//     }
//   }

//   void draw(uint8_t x, uint8_t y) {
//     buffer[y][x] = 1;
//   }

//   void erase(uint8_t x, uint8_t y) {
//     buffer[y][x] = 0;
//   }

// private:
//   void print_line_to_serial() {
//     for (uint8_t x = 0; x < rows; x++) {
//       Serial.print('-');
//     }
//     Serial.println();
//   }
// };

// LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
// Display display(16 * 2, 2 * 2);

// void setup() {
//   Serial.begin(9600);  // open the serial port at 9600 bps:
//   lcd.begin(16, 2);
//   lcd.clear();

//   for (uint8_t i = 0; i < display.columns; i++) {
//     display.draw(i, 3);
//     display.draw(i, 2);
//     display.draw(i, 1);
//   }
//   display.erase(1, 1);

//   Serial.println("Serial Port Initalized...");
//   display.print_to_serial();
//   display.print_to_lcd(lcd);
// }

// void loop() {}
