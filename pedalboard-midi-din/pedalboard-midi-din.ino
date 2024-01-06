// Name: Arduino Midi Pedalboard Encoder
// Created: Dec. 5, 2023
// Author: SSchaub
// Acknowledgements: Larason2

// Pedalboard bottom (rows - read these)
byte SCAN_PINS[] = { 46, 44, 42, 40, 38, 36 }; // matrix "rows"
// Pedalboard top (columns)
byte WRITE_PINS[] = { 34, 32, 30, 28, 26, 24, 22 }; // matrix "columns"

#define NUM_SCAN_PINS (sizeof(SCAN_PINS) / sizeof(SCAN_PINS[0]))
#define NUM_WRITE_PINS (sizeof(WRITE_PINS) / sizeof(WRITE_PINS[0]))

byte midiMatrix[NUM_SCAN_PINS][NUM_WRITE_PINS] = {
{0, 65, 59, 53, 47, 41, 0}, 
{0, 64, 58, 52, 46, 40, 0}, 
{0, 63, 57, 51, 45, 39, 0}, 
{0, 62, 56, 50, 44, 38, 0}, 
{67, 61, 55, 49, 43, 37, 0}, 
{0, 66, 60, 54, 48, 42, 36}, 
};

const byte channel = 4; // channels are 0-based
const byte NOTE_ON = 0x90 | channel;
const byte  NOTE_OFF = 0x80 | channel;
const int velocity = 100;

unsigned long keyStatus[70];


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
  
  // Read Pedalboard
  for (int col = 0; col < NUM_WRITE_PINS; ++col) {
    pinMode(WRITE_PINS[col],  OUTPUT);
    digitalWrite(WRITE_PINS[col], LOW);
    for (int row = 0; row < NUM_SCAN_PINS; ++row) {
      bool pedalDown = !digitalRead(SCAN_PINS[row]);
      byte midiNote = midiMatrix[row][col];
      if (midiNote) {
        if (pedalDown) {
          if (!keyStatus[midiNote]) {
            keyStatus[midiNote] = millis();
            Serial.write(NOTE_ON);
            Serial.write(midiNote);
            Serial.write(100);
          }
        } else {
          if (keyStatus[midiNote] && (millis() - keyStatus[midiNote] > 200)) {
            keyStatus[midiNote] = 0;
            Serial.write(NOTE_OFF);
            Serial.write(midiNote);
            Serial.write(100);
          }
        }
      }
    }
    pinMode(WRITE_PINS[col],  INPUT);
  }

  
}
