//-----------DECLARACIONES-------------------------------------
#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

//------PINES-----------*
int FSR1 = A0;
int FSR2 = A1;
int FSR3 = A2;
int FSR4 = A3;
int FSR5 = A4;
//------pines-----------*

//------funciones-----------*
boolean play[5] = {true,true,true,true,true};
//-----------FIN DECLARACIONES---------------------------------
void setup() {
MIDI.begin();//0 al 127 . 59 SI
Serial.begin(9600);
}

// FUNCIONES :D
// ------------------------------------------------------------

void suena(int nota,int boton){
  MIDI.sendNoteOn(nota,127,boton);
}

void para(int nota,int boton){
  MIDI.sendNoteOff(nota,127,boton);
}
//------------------------------------------------------------
//FIN FUNCIONES :D

void loop() {
  int vFSR1 = analogRead(FSR1);
  int vFSR2 = analogRead(FSR2);
  int vFSR3 = analogRead(FSR3);
  int vFSR4 = analogRead(FSR4);
  int vFSR5 = analogRead(FSR5);

  int mapa1 = map(vFSR1, 0, 980, 0,100);
  int mapa2 = map(vFSR2, 0, 980, 0,100);
  int mapa3 = map(vFSR2, 0, 980, 0,100);
  int mapa4 = map(vFSR2, 0, 980, 0,100);
  int mapa5 = map(vFSR2, 0, 980, 0,100);

// -------------------NOTAS PENTATONICAS----------------------
int nota1 = 72; // DO
int nota2 = 74; // RE
int nota3 = 76; // MI
int nota4 = 79; // SOL
int nota5 = 81; // LA
//--------------------FIN NOTAS-------------------------------

 

 

//----------------------------BOTON 1-------------------------------
  if (mapa1>10){
    if (play[0]){
      suena(nota1,1);//nota,boton
      play[0] = false;
      }
    }
  else{
    para(nota1,1);
    play[0] = true;
    }
//----------------------------BOTON 2-----------------------------------
  if (mapa2>10){
    if (play[1]){
      suena(nota2,2);//nota,boton
      play[1] = false;
      }
    }
  else {
    para(nota2,2);
    play[1] = true;
    }
//----------------------------BOTON 3-----------------------------------
  if (mapa3>10){
    if (play[2]){
      suena(nota3,3);//nota,boton
      play[2] = false;
      }
    }
  else {
    para(nota3,3);
    play[2] = true;
    }
//----------------------------BOTON 4-----------------------------------
  if (mapa4>10){
    if (play[3]){
      suena(nota4,4);//nota,boton
      play[3] = false;
      }
    }
  else{
    para(nota4,4);
    play[3] = true;
    }
//----------------------------BOTON 5-----------------------------------
  if (mapa5>10){
    if (play[4]){
      suena(nota5,5);//nota,boton
      play[4] = false;
      }
    }
  else{
    para(nota5,5);
    play[4] = true;
    }
//----------------------------FIN-----------------------------------
delay(10);
}
