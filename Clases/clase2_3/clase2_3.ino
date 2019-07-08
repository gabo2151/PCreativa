int potPin = A0;
int value = 0;
int percent = 0;
int ledR = 9;
int ledG = 10;
int ledB = 11;

void setup() {
  Serial.begin(9600);
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
}

void loop() {
  value = analogRead(potPin);
  percent = map(value, 0, 1023, 0, 255);
  Serial.print("Potenciometro = ");
  Serial.print( (percent/255.0)*100 );
  Serial.println("%");
  analogWrite(ledR, (percent / 2));
  analogWrite(ledG, percent);
  analogWrite(ledB, percent);
}
