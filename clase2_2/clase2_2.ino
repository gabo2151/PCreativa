int buttonPin = 2;
int buttonState = 0;
int led = 9;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    Serial.println("Cerrado");
    analogWrite(led, 255);
  }
  else {
    Serial.println("Abierto");
    analogWrite(led, 0);
  }
}
