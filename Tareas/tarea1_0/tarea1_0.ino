#define LEDPIN     13     // status LED pin
#define PIEZOTHRESHOLD 1000  // analog threshold for piezo sensing

int val;

void setup() {
  pinMode(LEDPIN, OUTPUT);
  Serial.begin(57600);   // set serial output rate
}

void loop() {
  val = analogRead(A0);
  if( val >= PIEZOTHRESHOLD ) {
    digitalWrite(LEDPIN,HIGH);  // indicate we're sending MIDI data
    Serial.print("Sensor: ");
    Serial.print(val);
    Serial.println();
    digitalWrite(LEDPIN,LOW);
  }
}
