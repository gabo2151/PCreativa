
#include <MPL115A1.h>
#define PRESSURE_5V 10

MPL115A1 sensor;

void setup() {
  pinMode(PRESSURE_5V, OUTPUT);
  digitalWrite(PRESSURE_5V, HIGH);
  Serial.begin(115200);
  sensor.begin();
}

void loop() {
  Serial.print("1: ");
  Serial.print( analogRead(A0) );
  Serial.print("; 2: ");
  Serial.print( analogRead(A1) );
  Serial.print("; 3: ");
  Serial.print( analogRead(A2) );
  Serial.print("; 4: ");
  Serial.print( analogRead(A3) );
  Serial.print("; hPa: ");
  Serial.println( sensor.pressure() );
  delay(100);
}
