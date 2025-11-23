#include <Servo.h>
#include <SD.h>

// --- Hardware Configuration ---
#define NUM_SERVOS 6
#define SERVO_UP_ANGLE 90
#define SERVO_DOWN_ANGLE 0
#define ACTUATION_DELAY 1000 // Time to hold the dot up (ms)
#define SD_CHIP_SELECT 10

// Servo Pin Mapping
const int SERVO_PINS[NUM_SERVOS] = {2, 3, 4, 5, 6, 7};

// Global Objects
Servo brailleServos[NUM_SERVOS];
File dataFile;

// --- Braille Lookup Table ---
// Maps characters 'a' through 'z' to 6-dot patterns (1 = UP, 0 = DOWN)
// This replaces the inefficient switch-case statement.
const bool BRAILLE_MAP[26][6] = {
  {1,0,0,0,0,0}, // a
  {1,0,1,0,0,0}, // b
  {1,1,0,0,0,0}, // c
  {1,1,0,1,0,0}, // d
  {1,0,0,1,0,0}, // e
  {1,1,1,0,0,0}, // f
  {1,1,1,1,0,0}, // g
  {1,0,1,1,0,0}, // h
  {0,1,1,0,0,0}, // i
  {0,1,1,1,0,0}, // j
  {1,0,0,0,1,0}, // k
  {1,0,1,0,1,0}, // l
  {1,1,0,0,1,0}, // m
  {1,1,0,1,1,0}, // n
  {1,0,0,1,1,0}, // o
  {1,1,1,0,1,0}, // p
  {1,1,1,1,1,0}, // q
  {1,0,1,1,1,0}, // r
  {0,1,1,0,1,0}, // s
  {0,1,1,1,1,0}, // t
  {1,0,0,0,1,1}, // u
  {1,0,1,0,1,1}, // v
  {0,1,1,1,0,1}, // w
  {1,1,0,0,1,1}, // x
  {1,1,0,1,1,1}, // y
  {1,0,0,1,1,1}  // z
};

void setup() {
  Serial.begin(9600);
  Serial.println("System Initializing...");

  // Initialize Servos
  for (int i = 0; i < NUM_SERVOS; i++) {
    brailleServos[i].attach(SERVO_PINS[i]);
    brailleServos[i].write(SERVO_DOWN_ANGLE); // Start at rest
  }

  // Initialize SD Card
  if (!SD.begin(SD_CHIP_SELECT)) {
    Serial.println("Error: SD Card initialization failed!");
    return; // Halt if SD fails
  }
  Serial.println("System Ready. Reading file...");
}

void loop() {
  dataFile = SD.open("example.txt");

  if (dataFile) {
    while (dataFile.available()) {
      char rawChar = dataFile.read();
      
      // Process only alphabetic characters
      if(isAlpha(rawChar)) {
        processCharacter(rawChar);
        delay(500); // Wait before next character
      }
    }
    dataFile.close();
    Serial.println("Translation Complete.");
    while(1); // Stop loop after finishing file
  } else {
    Serial.println("Error: Could not open example.txt");
    delay(2000); // Retry delay
  }
}

/**
 * Core Logic: Converts a character to servo movements
 */
void processCharacter(char c) {
  // Convert upper case to lower case for mapping
  c = toLowerCase(c);
  
  // Calculate index (a = 0, b = 1, etc.)
  int index = c - 'a';

  // Safety check to prevent array out of bounds
  if (index < 0 || index > 25) return;

  Serial.print("Translating: ");
  Serial.println(c);

  actuateBraille(index);
}

/**
 * Physical Actuation: Moves servos based on the lookup index
 */
void actuateBraille(int mapIndex) {
  // 1. Move all required servos UP simultaneously (Parallel Actuation)
  for (int i = 0; i < NUM_SERVOS; i++) {
    if (BRAILLE_MAP[mapIndex][i] == 1) {
      brailleServos[i].write(SERVO_UP_ANGLE);
    }
  }

  // 2. Hold the pattern for the user to feel
  delay(ACTUATION_DELAY);

  // 3. Reset all servos DOWN simultaneously
  resetServos();
}

void resetServos() {
  for (int i = 0; i < NUM_SERVOS; i++) {
    brailleServos[i].write(SERVO_DOWN_ANGLE);
  }
}
