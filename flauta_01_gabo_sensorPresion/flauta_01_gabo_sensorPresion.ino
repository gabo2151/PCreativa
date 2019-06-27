//-----------DECLARACIONES-------------------------------------
#include <MIDI.h>
#include <SPI.h>
#include <MPL115A1.h>

MPL115A1 sensor;

MIDI_CREATE_DEFAULT_INSTANCE();

//------PINES-----------*
int FSR[5] = {A0, A1, A2, A3, A4};
//------pines-----------*

//------funciones-----------*
boolean play[5] = {true, true, true, true, true};
//-----------FIN DECLARACIONES---------------------------------
void setup() {
  MIDI.begin();//0 al 127 . 59 SI
  Serial.begin(115200);
  sensor.begin();
}

// FUNCIONES :D
// ------------------------------------------------------------

void suena(int nota,int boton){
  MIDI.sendNoteOn( nota, 127, boton );
}

void para(int nota,int boton){
  MIDI.sendNoteOff( nota, 127, boton );
}

int vFSR1, vFSR2, vFSR3, vFSR4, vFSR5;
int mapa1, mapa2, mapa3, mapa4, mapa5;

void loop() {
//------------------------------------------------------------
//FIN FUNCIONES :D
  vFSR1 = analogRead( FSR[0] );
  vFSR2 = analogRead( FSR[1] );
  vFSR3 = analogRead( FSR[2] );
  vFSR4 = analogRead( FSR[3] );
  vFSR5 = analogRead( FSR[4] );

  mapa1 = map( vFSR1, 0, 980, 0, 100 );
  mapa2 = map( vFSR2, 0, 980, 0, 100 );
  mapa3 = map( vFSR2, 0, 980, 0, 100 );
  mapa4 = map( vFSR2, 0, 980, 0, 100 );
  mapa5 = map( vFSR2, 0, 980, 0, 100 );

// -------------------NOTAS PENTATONICAS----------------------
  int nota[8] = {72, 74, 76, 79, 81, 83, 85, 88};
//--------------------FIN NOTAS-------------------------------

//----------------------------BOTON 1-------------------------------
  if (mapa1>10){
    if (play[0]){
      suena(nota[0],1);//nota,boton
      play[0] = false;
      }
    }
  else {
    para(nota[0],1);
    play[0] = true;
    }
//----------------------------BOTON 2-----------------------------------
  if (mapa2>10){
    if (play[1]){
      suena(nota[1],2);//nota,boton
      play[1] = false;
      }
    }
  else {
    para(nota[1],2);
    play[1] = true;
    }
//----------------------------BOTON 3-----------------------------------
  if (mapa3>10){
    if (play[2]){
      suena(nota[2],3);//nota,boton
      play[2] = false;
      }
    }
  else {
    para(nota[2],3);
    play[2] = true;
    }
//----------------------------BOTON 4-----------------------------------
  if (mapa4>10){
    if (play[3]){
      suena(nota[3],4);//nota,boton
      play[3] = false;
      }
    }
  else{
    para(nota[3],4);
    play[3] = true;
    }
//----------------------------BOTON 5-----------------------------------
  if (mapa5>10){
    if (play[4]){
      suena(nota[4],5);//nota,boton
      play[4] = false;
      }
    }
  else{
    para(nota[4],5);
    play[4] = true;
    }
//----------------------------FIN-----------------------------------
delay(10);
}
