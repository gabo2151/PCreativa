#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  MIDI.begin();
  Serial.begin(115200);
}

int note1;
int note2;
int note3;
int ran1;
int ran2;
int ran3;

void loop() {
  note1 = 20 + random(60);
  note2 = random(80);
  note3 = random(80);
  ran1 = random(150);
  ran2 = random(150);
  ran3 = random(150);
  MIDI.sendNoteOn(note1, 127, 1);
  delay(ran1);
  MIDI.sendNoteOn(note2, 127, 2);
  delay(ran2);
  MIDI.sendNoteOn(note3, 127, 3);
  delay(ran3);
  MIDI.sendNoteOff(note1, 127, 1);
  delay(20);
  MIDI.sendNoteOff(note2, 127, 2);
  delay(20);
  MIDI.sendNoteOff(note3, 127, 3);
  delay(20);
}
