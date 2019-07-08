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

int vFSR[5];
int mapa[5];

float hPa;
int vol;

//-----------FIN DECLARACIONES---------------------------------
void setup() {
  MIDI.begin();
  Serial.begin(115200);
  sensor.begin();
}

// FUNCIONES :D
// ------------------------------------------------------------
void suena( int nota, int vol, int canal ){
  MIDI.sendNoteOn( nota, vol, canal );
}

void para( int nota, int vol, int canal ){
  MIDI.sendNoteOff( nota, vol, canal );
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
  vol = map(hPa, 1010.0, 1045.0, 0, 127);
  vol = 127;

  // -------------------NOTAS PENTATONICAS----------------------
  int nota[8] = {60, 62, 64, 65, 67, 69, 71, 72};
  //--------------------FIN NOTAS-------------------------------

  //----------------------------BOTON 1-5 ----------------------
  for (int i=0; i<4; i++) { // Cambiar a 5 si es que se agrega el quinto boton
    if ( mapa[i] > 10 ) {
      if ( play[i] ){
        //suena( nota[i], vol, i+1 );
        pres[i] = true;
        play[i] = false;
      }
    }
    else {
      //para ( nota[i], vol, i+1 );
      pres[i] = false;
      play[i] = true;
    }
  }
  if ( hPa > 1000 ) {
    if      (  pres[0] && !pres[1] && !pres[2] ){
      MIDI.sendNoteOn( nota[0], vol, 1 );
    }
    else if ( !pres[0] &&  pres[1] && !pres[2] ){
      MIDI.sendNoteOn( nota[1], vol, 1 );
    }
    else if ( !pres[0] && !pres[1] &&  pres[2] ){
      MIDI.sendNoteOn( nota[2], vol, 1 );
    }
    else if (  pres[0] &&  pres[1] && !pres[2] ){
      MIDI.sendNoteOn( nota[3], vol, 1 );
    }
    else if (  pres[0] && !pres[1] &&  pres[2] ){
      MIDI.sendNoteOn( nota[4], vol, 1 );
    }
    else if ( !pres[0] &&  pres[1] &&  pres[2] ){
      MIDI.sendNoteOn( nota[5], vol, 1 );
    }
    else if (  pres[0] &&  pres[1] &&  pres[2] ){
      MIDI.sendNoteOn( nota[6], vol, 1 );
    }
    else {
      MIDI.sendNoteOn( nota[7], vol, 1 );
    }
  }
  else {
    MIDI.sendNoteOff( nota[0], vol, 1);
    MIDI.sendNoteOff( nota[1], vol, 1);
    MIDI.sendNoteOff( nota[2], vol, 1);
    MIDI.sendNoteOff( nota[3], vol, 1);
    MIDI.sendNoteOff( nota[4], vol, 1);
    MIDI.sendNoteOff( nota[5], vol, 1);
    MIDI.sendNoteOff( nota[6], vol, 1);
    MIDI.sendNoteOff( nota[7], vol, 1);
  }
  //----------------------------FIN-----------------------------
  delay(10);
}
