int flexPin = A0;
const int pinBuzzer = 3;
int ledR = 9;
int ledG = 10;
int ledB = 11;

void setup() {
  Serial.begin(9600);
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
}

int varT = 0;

void loop() {
  int flexValue = analogRead(flexPin);
  int flextone = map(flexValue, 320, 480, 261, 494);

  //tone(pinBuzzer, flextone);

  //Serial.print("Flexion = ");
  //Serial.print(flextone);
  //Serial.println("%");
  //delay(100);
  
  varT = ((flextone-120)*(255/450.0));
  Serial.print("Flexion = ");
  Serial.print(varT);
  Serial.println("%");
  
  if(varT < 85){
    analogWrite(ledR, varT * (255/85));
    analogWrite(ledG, 0);
    analogWrite(ledB, 0);
  }
  else if ( (85 <= varT) && (varT < 170) ) {
    analogWrite(ledR, 0);
    analogWrite(ledG, ((varT-85) * (255/85)));
    analogWrite(ledB, 0);
  }
  else {
    analogWrite(ledR, 0);
    analogWrite(ledG, 0);
    analogWrite(ledB, ((varT-170) * (255/85)));
  }
  //analogWrite(ledR, varT);
}
