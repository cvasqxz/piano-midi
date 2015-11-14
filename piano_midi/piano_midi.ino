//ARDUINO MIDI LIBRARY
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
    pinMode(i, INPUT_PULLUP);
  }

  //INICIAR PINES DE SALIDA
  for(int i = 2; i < 6; i++){
    pinMode(i, OUTPUT);  
  }
}

void loop() {
  //ACTIVACION DE PINES DE ENTRADA
  for(int i = 2; i < 6; i++){
    //RESETEAR LOS PINES
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);

    //ACTIVAR PIN
    digitalWrite(i, LOW);

    //LECTURA DE PINES DE SALIDA
    for(int j = 6; j < 14; j++){

      //DEFINIR NOTA
      int aux = (j-6) + (i-2)*8;
            
      //DETECTAR TECLA PRESIONADA
      if (digitalRead(i) == LOW && digitalRead(j) == LOW){
        nota_presente[aux] = HIGH;
      }
      else{
        nota_presente[aux] = LOW;
      }

      //ENVIAR PACKET ON/OFF
      if(nota_presente[aux] != nota_pasado[aux]){
        if(nota_presente[aux] == HIGH){
          //ENVIAR NOTE ON
          MIDI.sendNoteOn(41 + aux, 127, (int)(2 + aux)/2);
        }
        else{
          //ENVIAR NOTE OFF
          MIDI.sendNoteOff(41 + aux, 0, (int)(2 + aux)/2);
        }
      }

      //COPIAR LA VARIABLE DEL PRESENTE AL PASADO
      nota_pasado[aux] = nota_presente[aux];
    }
  }
}
