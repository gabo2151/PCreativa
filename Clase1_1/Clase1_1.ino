int LEDG = 9;
int LEDR = 10;
int LEDB = 11;

void setup() {
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
}

void loop() {
  /*for(int i = 0; i < 256; i+=5) {
    for(int j = 0; j < 256; j+=5) {
      for(int k = 0; k < 256; k+=5) {
        analogWrite(LEDR, i);
        analogWrite(LEDG, j);
        analogWrite(LEDB, k);
        //delay(10);
      }
    }
  }
  for(int i = 255; i >= 0; i-=5){
    analogWrite(LEDR, i);
    analogWrite(LEDG, i);
    analogWrite(LEDB, i);
    delay(30);
  }*/
  analogWrite(LEDR, random(255));
  analogWrite(LEDG, random(255));
  analogWrite(LEDB, random(255));
  delay(200);
}
