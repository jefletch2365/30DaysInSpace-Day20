/* Day 20 Creative Day
  Make keypad that is programmed to output specific colors

 { Red (255,0,0),       Green (0,255,0),       Blue (0,0,255),      High (255,255,255) }
 { Magenta (255,0,255),   Cyan (0,255,255),        Yellow (255,255,0),  Medium (100,100,100) }
 { Orange (255,128,0),    Azure (0,128,255),       Violet (128,0,255),    Low (20, 20, 20) }
 { Rose (255,0,128),      Chartruese (128,255,0),  Spring (0,255,128),    off };
*/
#include <Keypad.h>
// Our keypad has 4 rows, each with 4 columns.
const byte ROWS = 4;
const byte COLS = 4;

// These constant arrays contain the pins connected to the keypad's row and column pins.
const byte ROW_PINS[ROWS] = { 5, 4, 3, 2 };
const byte COL_PINS[COLS] = { 6, 7, 8, 13 };

typedef struct {
    byte r;
    byte g;
    byte b;
} Color;

const Color COLORS[ROWS][COLS] = {
    { {255, 0, 0}, {0, 255, 0}, {0, 0, 255}, {255, 255, 255} },  // Row 0
    { {255, 0, 255}, {0, 255, 255}, {255, 255, 0}, { 100, 100, 100 } },  // Row 1
    { {255, 128, 0}, {0, 128, 255}, {128, 0, 255}, { 20, 20, 20 } },  // Row 2
    { {255, 0, 128}, {128, 255, 0}, {0, 255, 128}, { 0, 0, 0 } }   // Row 3
};

char keys[ROWS][COLS] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};

Keypad heroKeypad = Keypad(makeKeymap(keys), ROW_PINS, COL_PINS, ROWS, COLS);

const byte RED_PIN = 11;    // pin controlling the red leg of our RGB LED
const byte GREEN_PIN = 10;  // pin ccontrolling the green leg of our RGB LED
const byte BLUE_PIN = 9;    // pin ccontrolling the blue leg of our RGB LED

void setup() {
  // put your setup code here, to run once:
  pinMode(RED_PIN, OUTPUT);        // Set light control pin as an OUTPUT
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  Serial.begin(9600); 
}

void loop() {
  // put your main code here, to run repeatedly:
  char pressedButton = heroKeypad.getKey();  // Wait until a button is pressed
   if (pressedButton) {
      int redValue = 0, greenValue = 0, blueValue = 0;
      for (int i = 0; i < ROWS; ++i) {
          for (int j = 0; j < COLS; ++j) {
            if (keys[i][j] == pressedButton) {
              redValue = COLORS[i][j].r;
              greenValue = COLORS[i][j].g;
              blueValue = COLORS[i][j].b; 

              analogWrite(RED_PIN, redValue);
              analogWrite(GREEN_PIN, greenValue);
              analogWrite(BLUE_PIN, blueValue);
              Serial.println(redValue);
              Serial.println(greenValue);
              Serial.println(blueValue);
            }
          }
      }    
    }
}

