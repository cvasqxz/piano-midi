#include <MIDI.h>

//CREAR INSTANCIA MIDI
MIDI_CREATE_DEFAULT_INSTANCE();

//VARIABLES DE ESTADO PASADO/PRESENTE
int nota_pasado[32];
int nota_presente[32];

void setup() {
// INICIAR MIDI
MIDI.begin();

//INICIAR PINES DE ENTRADA (PULL UP)
for(int i = 6; i < 14; i++){
  pinMode(i, OUTPUT);
  }

//INICIAR PINES DE SALIDA
for(int i = 2; i < 6; i++){
  pinMode(i, INPUT_PULLUP);  
  }
}

void loop() {

  for(int i = 6; i < 14; i++){
    //RESETEAR LOS PINES
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(13, HIGH);

    //ACTIVAR PIN DEL FOR
    digitalWrite(i, LOW);

    //LECTURA DE PINES
    for(int j = 2; j < 6; j++){
      //DEFINIR NOTA
      int aux = (i - 6) + (j-2)*8;
            
      //DETECTAR TECLA PRESIONADA
      if (digitalRead(j) == LOW && digitalRead(i) == LOW){
        nota_presente[aux] = HIGH;
        }
      else{
        nota_presente[aux] = LOW;
      }

      //ENVIAR PACKET ON/OFF
      if(nota_presente[aux] != nota_pasado[aux]){
        if(nota_presente[aux] == HIGH){
          //ENVIAR NOTE ON
          MIDI.sendNoteOn(41 + aux,127,1);
          }
        else{
          //ENVIAR NOTE OFF
          MIDI.sendNoteOff(41 + aux,0,1);
        }
      }

      //COPIAR LA VARIABLE DEL PRESENTE AL PASADO
      nota_pasado[aux] = nota_presente[aux];
    }
  }
}

