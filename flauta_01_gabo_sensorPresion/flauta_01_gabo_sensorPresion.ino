//-----------DECLARACIONES-------------------------------------
#include <MIDI.h>
#include <SPI.h>
#include <MPL115A1.h>

MPL115A1 sensor;

MIDI_CREATE_DEFAULT_INSTANCE();

//------PINES-----------*
int FSR[5] = {A0, A1, A2, A3, A4};

boolean play[5] = {true, true, true, true, true};

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
  //vFSR[4] = analogRead( FSR[4] );

  mapa[0] = map( vFSR[0], 0, 980, 0, 100 );
  mapa[1] = map( vFSR[1], 0, 980, 0, 100 );
  mapa[2] = map( vFSR[2], 0, 980, 0, 100 );
  mapa[3] = map( vFSR[3], 0, 980, 0, 100 );
  //mapa[4] = map( vFSR[4], 0, 980, 0, 100 );

  hPa = sensor.pressure();
  vol = map(hPa, 1010.0, 1045.0, 0, 127);

  // -------------------NOTAS PENTATONICAS----------------------
  int nota[8] = {72, 74, 76, 79, 81, 83, 85, 88};
  //--------------------FIN NOTAS-------------------------------

  //----------------------------BOTON 1-5 ----------------------
  for (int i=0; i<4; i++) { // Cambiar a 5 si es que se agrega el quinto boton
    if ( mapa[i] > 10 ) {
      if ( play[i] ){
        suena( nota[i], vol, i);
        play[i] = false;
      }
    }
    else {
      para ( nota[i], vol, i );
      play[i] = true;
    }
  }
  //----------------------------FIN-----------------------------
  delay(10);
}
