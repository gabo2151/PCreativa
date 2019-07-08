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

int vFSR[5];
int mapa[5];

float hPa;
float b_a, b_b;
int vol;

//-----------FIN DECLARACIONES---------------------------------
void setup() {
  MIDI.begin();
  Serial.begin(115200);
  sensor.begin();
}

// FUNCIONES :D
// ------------------------------------------------------------
void suena( int nota, int vol, int canal, bool oct ){
  if (oct) {
    MIDI.sendNoteOn( nota+12, vol, canal );
  }
  else {
    MIDI.sendNoteOn( nota, vol, canal );
  }
}

void para( int nota, int vol, int canal, bool oct ){
  if (oct) {
    MIDI.sendNoteOn( nota+12, vol, canal );
  }
  else {
    MIDI.sendNoteOn( nota, vol, canal );
  }
}

//------------------------------------------------------------
//FIN FUNCIONES :D

void loop() {
  vFSR[0] = analogRead( FSR[0] );
  vFSR[1] = analogRead( FSR[1] );
  vFSR[2] = analogRead( FSR[2] );
  vFSR[3] = analogRead( FSR[3] );
  vFSR[4] = analogRead( FSR[4] );

  mapa[0] = map( vFSR[0], 0, 980, 0, 100 );
  mapa[1] = map( vFSR[1], 0, 980, 0, 100 );
  mapa[2] = map( vFSR[2], 0, 980, 0, 100 );
  mapa[3] = map( vFSR[3], 0, 980, 0, 100 );
  mapa[4] = map( vFSR[4], 0, 980, 0, 100 );

  hPa = sensor.pressure();
  if (calibracion){
    MIDI.sendNoteOn(60, 100, 2);
    delay(1500);
    b_a = hPa - 2.0;
    b_b = hPa + 35.0;
    MIDI.sendNoteOff(60, 100, 2);
    calibracion = false;
  }
  vol = map(hPa, b_a, b_b, 0, 127);
  //vol = 127;

  // -------------------NOTAS PENTATONICAS----------------------
  int nota[8] = {60, 62, 64, 65, 67, 69, 71, 72};
  //--------------------FIN NOTAS-------------------------------

  //----------------------------BOTON 1-4 ----------------------
  for (int i=0; i<4; i++) {
    if ( mapa[i] > 10 ) {
      if ( play[i] ){
        pres[i] = true;
        play[i] = false;
      }
    }
    else {
      pres[i] = false;
      play[i] = true;
    }
  }
  if ( hPa > (b_a+2.0) ) {
    if      (  pres[0] && !pres[1] && !pres[2] ){
      suena( nota[0], vol, 1, pres[3] );
    }
    else if ( !pres[0] &&  pres[1] && !pres[2] ){
      suena( nota[1], vol, 1, pres[3] );
    }
    else if ( !pres[0] && !pres[1] &&  pres[2] ){
      suena( nota[2], vol, 1, pres[3] );
    }
    else if (  pres[0] &&  pres[1] && !pres[2] ){
      suena( nota[3], vol, 1, pres[3] );
    }
    else if (  pres[0] && !pres[1] &&  pres[2] ){
      suena( nota[4], vol, 1, pres[3] );
    }
    else if ( !pres[0] &&  pres[1] &&  pres[2] ){
      suena( nota[5], vol, 1, pres[3] );
    }
    else if (  pres[0] &&  pres[1] &&  pres[2] ){
      suena( nota[6], vol, 1, pres[3] );
    }
    else {
      suena( nota[7], vol, 1, pres[3] );
    }
  }
  else {
    para( nota[0], vol, 1, pres[3]);
    para( nota[1], vol, 1, pres[3]);
    para( nota[2], vol, 1, pres[3]);
    para( nota[3], vol, 1, pres[3]);
    para( nota[4], vol, 1, pres[3]);
    para( nota[5], vol, 1, pres[3]);
    para( nota[6], vol, 1, pres[3]);
    para( nota[7], vol, 1, pres[3]);
  }
  //----------------------------FIN-----------------------------
  delay(10);
}
