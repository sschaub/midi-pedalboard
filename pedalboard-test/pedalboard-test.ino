// Name: Pedalboard test utility
// Created: Dec. 5, 2023
// Author: SSchaub
// Acknowledgements: Larason2


// Pedalboard bottom (rows - read these)
byte SCAN_PINS[] = { A0, A1, A2, A3, A4, A5 }; // matrix "rows"
// Pedalboard top (columns)
byte WRITE_PINS[] = { 0, 1, 2, 3, 4, 5, 6 }; // matrix "columns"

#define NUM_SCAN_PINS (sizeof(SCAN_PINS) / sizeof(SCAN_PINS[0]))
#define NUM_WRITE_PINS (sizeof(WRITE_PINS) / sizeof(WRITE_PINS[0]))

byte keys[NUM_SCAN_PINS][NUM_WRITE_PINS];


void setup() {
  // Start Serial
  Serial.begin(31250);

  // Setup input pins
  for (int i = 0; i < NUM_SCAN_PINS; i++)
    pinMode(SCAN_PINS[i], INPUT_PULLUP);

  // Setup output pins
  for (int i = 0; i < NUM_WRITE_PINS; i++)
    pinMode(WRITE_PINS[i], INPUT);

}

void loop() {
  
  // Scan pedalboard
  for (int col = 0; col < NUM_WRITE_PINS; ++col) {
    pinMode(WRITE_PINS[col],  OUTPUT);
    digitalWrite(WRITE_PINS[col], LOW);

    for (int row = 0; row < NUM_SCAN_PINS; ++row) {
      keys[row][col] = !digitalRead(SCAN_PINS[row]);
    }
    pinMode(WRITE_PINS[col],  INPUT);
  }

  // Report results
  for (int row = 0; row < NUM_SCAN_PINS; ++row) {
    Serial.print("r");
    Serial.print(row);
    Serial.print("[");
    for (int col = 0; col < NUM_WRITE_PINS; ++col) {
      Serial.print(keys[row][col] ? '*' : '-');
    }
    Serial.print("] ");
  }

  for (int row = 0; row < NUM_SCAN_PINS; ++row) {
    for (int col = 0; col < NUM_WRITE_PINS; ++col) {
      if (keys[row][col]) {
        Serial.print('r');
        Serial.print(row);
        Serial.print(',');
        Serial.print('c');
        Serial.print(col);
        Serial.print(' ');
      }
    }
  }

  Serial.println();

  // 500ms delay
  delay(500);

  
}
