/*
 Sample Sketch for MPL115A1 Breakout board Sensor Library for Arduino
   created by NeoCat <neocat@neocat.jp>
 
 Circuit:
   MPL115A1 breakout board is connected to pins 8, 9, 11 - 13 as default:
   SHDN: pin 9 (default, configurable)
   CSN:  pin 8 (default, configurable)
   SDO/DOUT/MISO: pin 12
   SDI/DIN/MOSI:  pin 11
   SCK: pin 13
*/

#include <MIDI.h>
#include <SPI.h>
#include <MPL115A1.h>

MPL115A1 sensor;

MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  Serial.begin(115200);
  sensor.begin();
}

bool turnOff = true;
int vol;

void loop() {
  float hPa = sensor.pressure();
  //Serial.print(hPa);
  //Serial.print(" hPa\n");
  //delay(50);

  vol = map(hPa, 1010.0, 1045.0, 0, 127);
  MIDI.sendNoteOn(60, vol, 1);
  delay(100);
  //if(turnOff){
  //  MIDI.sendNoteOn(vol, 127, 1);
  //  turnOff = false;
  //}
}
