#include <MIDI.h>
#define LEDPIN     13     // status LED pin
#define PIEZOTHRESHOLD 500  // analog threshold for piezo sensing

MIDI_CREATE_DEFAULT_INSTANCE();

int val, note, tempo;

void setup() {
  pinMode(LEDPIN, OUTPUT);
  Serial.begin(115200);   // set serial output rate
}

void loop() {
  val = analogRead(A0);
  if( val >= PIEZOTHRESHOLD ) {
    digitalWrite(LEDPIN,HIGH);  // indicate we're sending MIDI data
    //Serial.print("Sensor: ");
    //Serial.print(val);
    //Serial.println();

    note = map(analogRead(A1), 0, 1023, 0, 127);
    //tempo = val * 0.5;
    MIDI.sendNoteOn(note, 127, 1);
    delay(50);
    MIDI.sendNoteOff(note, 127, 1);
    
    digitalWrite(LEDPIN,LOW);
  }
}
