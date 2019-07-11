//-----------DECLARACIONES-------------------------------------
#include <MIDI.h>
#include <SPI.h>
#include <MPL115A1.h>

MPL115A1 sensor;

MIDI_CREATE_DEFAULT_INSTANCE();

//------PINES-----------*
int FSR[5] = {A0, A1, A2, A3, A4};

boolean play[5] = {true, true, true, true, true};
boolean pres[5] = {false, false, false, false, false};
boolean calibracion = true;

int nt;
int vFSR[5];
int mapa[5];

float hPa;
float b_a, b_b;
int vol;

int curr_note;

//-----------FIN DECLARACIONES---------------------------------
void setup() {
  MIDI.begin();
  Serial.begin(115200);
  sensor.begin();
  nt = -1;
}

// FUNCIONES :D
// ------------------------------------------------------------
void suena( int nota, int vol, int canal){  
  MIDI.sendNoteOn ( nota, vol, canal );
}


void para( int nota, int vol, int canal){
  MIDI.sendNoteOff( nota, vol, canal );
}

//------------------------------------------------------------
//FIN FUNCIONES :D

void loop() {
  for (int i=0; i<5; i++){
    vFSR[i] = analogRead( FSR[i] );
    mapa[i] = map( vFSR[i], 0, 980, 0, 100 );
  }
  
  int pAux = 0;
  for (int j=0; j<5; j++){
    pAux = pAux + sensor.pressure();
  }
  hPa = pAux/5;
  
  if (calibracion){
    MIDI.sendNoteOn(60, 100, 2);
    delay(1500);
    b_a = hPa + 2.0;
    b_b = hPa + 30.0;
    MIDI.sendNoteOff(60, 100, 2);
    calibracion = false;
  }
  vol = map(hPa, b_a, b_b, 20, 127);

  // -------------------NOTAS PENTATONICAS----------------------
  // 100 -> 1 <- Do  = 60
  // 010 -> 2 <- Re  = 62
  // 001 -> 4 <- Mi  = 64
  // 110 -> 3 <- Fa  = 65
  // 101 -> 5 <- Sol = 67
  // 011 -> 6 <- La  = 69
  // 111 -> 7 <- Si  = 71
  // 000 -> 0 <- Do. = 72
  int nota[8] = {72, 60, 62, 65, 64, 67, 69, 71, 84, 72, 74, 77, 76, 79, 81, 83};
  //--------------------FIN NOTAS-------------------------------

  //-------------------------- BOTONES -------------------------
  for (int i=0; i<4; i++) {
    if ( mapa[i] > 5 && hPa > (b_a)) {
        pres[i] = true;
    }
    else {
      pres[i] = false;
    }
  }
  if ( hPa > (b_a) ) {
    curr_note = 0;
    if (pres[0]) { curr_note += 1; }
    if (pres[1]) { curr_note += 2; }
    if (pres[2]) { curr_note += 4; }
    if (pres[3]) { curr_note += 8; }
    if ( nt != curr_note ) {
      suena( nota[curr_note], vol, 1 );
      nt = curr_note;
    }
    for (int i=0; i<16; i++){
      if (i != nt){
        para( nota[i], vol, 1);
      } 
    }
  }
  else {
    if (nt != -1) {
      nt = -1;
      for (int i=0; i<16; i++){
        para (nota[i], vol, 1);
      }
    }
  }
  //----------------------------FIN-----------------------------
}
