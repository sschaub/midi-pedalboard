// Name: Arduino Pedalboard Matrix Creation Utility
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

char* notes[]={"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};


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

int midiNote = 36;
bool prompt = true;

void loop() {
  
  // Read Pedalboard

  bool foundNew = false;

  if (prompt) {
    int offset = ((midiNote - 36) % 12);
    int octave = (midiNote - 36) / 12 + 1;
    Serial.print("Press ");
    Serial.print(notes[offset]);
    Serial.print(" (octave ");
    Serial.print(octave);
    Serial.print(", MIDI Note ");
    Serial.print(midiNote);
    Serial.println("):");
    prompt = false;
  }

  for (int col = 0; col < NUM_WRITE_PINS; ++col) {
    pinMode(WRITE_PINS[col],  OUTPUT);
    digitalWrite(WRITE_PINS[col], LOW);
    for (int row = 0; row < NUM_SCAN_PINS; ++row) {
      bool pedalDown = !digitalRead(SCAN_PINS[row]);
      if (pedalDown && !keys[row][col]) {
        foundNew = prompt = true;
        keys[row][col] = midiNote;
        ++midiNote;
      }
    }
    pinMode(WRITE_PINS[col],  INPUT);
  }

  if (!foundNew)
   return;

  for (int row = 0; row < NUM_SCAN_PINS; ++row) {
    Serial.print('{');
    for (int col = 0; col < NUM_WRITE_PINS; ++col) {
      Serial.print(keys[row][col]);
      if (col < NUM_WRITE_PINS - 1)
        Serial.print(", ");
    }
    Serial.println("}, ");
  }

  Serial.println();

  
}
