#include <Arduino.h>
#include "ATUADORES.h"
#include "BUZZER.h"
#include "CONTATORA.h"
#include "LEDS.h"
#include "ENTRADA.h"
#include "VT.h"

#define pinoLedBranco 1
#define pinoLedLaranja 2
#define pinoLedAzul 7 
#define pinoBuzzer 6
#define pinoContatora 5
#define pinoVT 3
#define pinoSensorToque 4

Leds ledBranco(pinoLedBranco);
Leds ledLaranja(pinoLedLaranja);
Leds ledAzul(pinoLedAzul);
Buzzer buzzer(pinoBuzzer);
Contatora contatora(pinoContatora);
ValidTransmittion VT(pinoVT);
Entradas sensorToque(pinoSensorToque);

unsigned long tempoAntigo = 0;                     // contador geral
unsigned long tempoAntigoBuzzer = 0;               // contador do buzzer
unsigned long tempoAntigoLedBranco = 0;           // contador do led amarelo
unsigned long tempoAntigoLedLaranja = 0;
unsigned long tempoAntigoLedAzul = 0; 

unsigned long intevaloBuzzer = 5000;

void setup(){

}
void loop(){
  unsigned long tempoAtual = millis();
  bool estaContando = false;

  if(VT.getEstado() == HIGH && !estaContando){
    buzzer.ligarAtuador(tempoAtual, tempoAntigoBuzzer, intevaloBuzzer);
    ledBranco.trocaTempo(tempoAntigoLedBranco, tempoAtual);

    tempoAntigo = tempoAtual;
    estaContando = true;

  }

  if(estaContando){
    if(VT.getEstado() == )
  }

}