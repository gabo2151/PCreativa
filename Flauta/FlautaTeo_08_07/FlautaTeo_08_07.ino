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

//-----------FIN DECLARACIONES---------------------------------
void setup() {
  MIDI.begin();
  Serial.begin(115200);
  sensor.begin();
  nt=-1;
}

// FUNCIONES :D
// ------------------------------------------------------------
void suena( int nota, int vol, int canal){
  
    MIDI.sendNoteOn( nota, vol, canal);
  }


void para( int nota, int vol, int canal){
  
    MIDI.sendNoteOff( nota, 0, canal );
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
  
  int pAux=0;
for (int j=0;j<5;j++){
  pAux = pAux + sensor.pressure();
  }
  hPa=pAux /5;
  
//  if (calibracion){
//    MIDI.sendNoteOn(60, 100, 2);
//    delay(1500);
//    b_a = hPa - 2.0;
//    b_b = hPa + 35.0;
//    MIDI.sendNoteOff(60, 100, 2);
//    calibracion = false;
//  }
b_a = 1014;
b_b = 1040;
  vol = map(hPa, b_a, b_b, 20, 127);
  //vol = 127;

  // -------------------NOTAS PENTATONICAS----------------------
  int nota[16] = {60, 62, 64, 65, 67, 69, 71, 72, 74, 76, 77, 79, 81, 83, 84, 86};
  //--------------------FIN NOTAS-------------------------------

  //----------------------------BOTON 1-3 ----------------------
  for (int i=0; i<4; i++) {
    if ( mapa[i] > 3 && hPa > (b_a)) {
     // if ( play[i] ){
        pres[i] = true;
       // play[i] = false;
     // }
    }
    else {
      pres[i] = false;
     // play[i] = true;
    }
  }
  if ( hPa > (b_a) ) {
    if      (  pres[0] && !pres[1] && !pres[2] && !pres[3] && nt != 0){
      suena( nota[0], vol, 1 );
      nt = 0;
      for (int i=0; i<8; i++){
     // if (i != 0){para( nota[i], vol, 1, pres[3]);} 
      }
      }
    
    else if ( !pres[0] &&  pres[1] && !pres[2] && !pres[3] && nt != 1 ){
      suena( nota[1], vol, 1);
       nt = 1;
        for (int i=0; i<8; i++){
     // if (i != 1){para( nota[i], vol, 1, pres[3]);} 
      }
    }
    else if ( !pres[0] && !pres[1] &&  pres[2] && !pres[3] && nt != 2){
      suena( nota[2], vol, 1);
       nt = 2;
        for (int i=0; i<8; i++){
     // if (i != 2){para( nota[i], vol, 1, pres[3]);} 
      }
    }
    else if (  pres[0] &&  pres[1] && !pres[2] && !pres[3] && nt != 3 ){
      suena( nota[3], vol, 1 );
       nt = 3;
        for (int i=0; i<8; i++){
     // if (i != 3){para( nota[i], vol, 1, pres[3]);} 
      }
    }
    else if (  pres[0] && !pres[1] &&  pres[2] && !pres[3] && nt != 4){
      suena( nota[4], vol, 1 );
       nt = 4;
        for (int i=0; i<8; i++){
     // if (i != 4){para( nota[i], vol, 1, pres[3]);} 
      }
    }
    else if ( !pres[0] &&  pres[1] &&  pres[2] && !pres[3] && nt != 5){
      suena( nota[5], vol, 1 );
       nt = 5;
        for (int i=0; i<8; i++){
     // if (i != 5){para( nota[i], vol, 1, pres[3]);} 
      }
    }
    else if (  pres[0] &&  pres[1] &&  pres[2] && !pres[3] && nt != 6){
      suena( nota[6], vol, 1 );
       nt = 6;
        for (int i=0; i<8; i++){
     // if (i != 6){para( nota[i], vol, 1, pres[3]);} 
      }
    }
      else if (  !pres[0] &&  !pres[1] &&  !pres[2] && !pres[3] && nt != 7){
      suena( nota[7], vol, 1 );
       nt = 7;
        for (int i=0; i<8; i++){
     // if (i != 6){para( nota[i], vol, 1, pres[3]);} 
      }
    }

      else  if      (  pres[0] && !pres[1] && !pres[2] && pres[3] && nt != 8){
      suena( nota[8], vol, 1 );
       nt = 8;
      for (int i=1; i<8; i++){
     // if (i != 0){para( nota[i], vol, 1, pres[3]);} 
      }
      }
    
    else if ( !pres[0] &&  pres[1] && !pres[2] && pres[3] && nt != 9){
      suena( nota[9], vol, 1 );
       nt = 9;
        for (int i=0; i<8; i++){
     // if (i != 1){para( nota[i], vol, 1, pres[3]);} 
      }
    }
    else if ( !pres[0] && !pres[1] &&  pres[2] && pres[3] && nt != 10 ){
      suena( nota[10], vol, 1 );
       nt = 10;
        for (int i=0; i<8; i++){
     // if (i != 2){para( nota[i], vol, 1, pres[3]);} 
      }
    }
    else if (  pres[0] &&  pres[1] && !pres[2] && pres[3] && nt != 11 ){
      suena( nota[11], vol, 1 );
       nt = 11;
        for (int i=0; i<8; i++){
     // if (i != 3){para( nota[i], vol, 1, pres[3]);} 
      }
    }
    else if (  pres[0] && !pres[1] &&  pres[2] && pres[3] && nt != 12){
      suena( nota[12], vol, 1 );
       nt = 12;
        for (int i=0; i<8; i++){
     // if (i != 4){para( nota[i], vol, 1, pres[3]);} 
      }
    }
    else if ( !pres[0] &&  pres[1] &&  pres[2] && pres[3] && nt != 13){
      suena( nota[13], vol, 1);
       nt = 13;
        for (int i=0; i<8; i++){
     // if (i != 5){para( nota[i], vol, 1, pres[3]);} 
      }
    }
    else if (  pres[0] &&  pres[1] &&  pres[2] && pres[3] && nt != 14){
      suena( nota[14], vol, 1 );
       nt = 14;
        for (int i=0; i<8; i++){
     // if (i != 6){para( nota[i], vol, 1, pres[3]);} 
      }
    }
      else if (  !pres[0] &&  !pres[1] &&  !pres[2] && pres[3] && nt != 15){
      suena( nota[15], vol, 1 );
       nt = 15;
        for (int i=0; i<8; i++){
     // if (i != 6){para( nota[i], vol, 1, pres[3]);} 
      }
    }

for (int i=0; i<16; i++){
      if (i != nt){para( nota[i], 0, 1);} 
      }
  
  }
  else {
    if (nt != -1) {
    nt = -1;
    para( nota[0], vol, 1);
    para( nota[1], vol, 1);
    para( nota[2], vol, 1);
    para( nota[3], vol, 1);
    para( nota[4], vol, 1);
    para( nota[5], vol, 1);
    para( nota[6], vol, 1);
    para( nota[7], vol, 1);
    para( nota[8], vol, 1);
    para( nota[9], vol, 1);
    para( nota[10], vol, 1);
    para( nota[11], vol, 1);
    para( nota[12], vol, 1);
    para( nota[13], vol, 1);
    para( nota[14], vol, 1);
    para( nota[15], vol, 1);
    
    }
  }
  //----------------------------FIN-----------------------------

}
