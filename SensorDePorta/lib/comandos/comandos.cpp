#include <Arduino.h>
#include "comandos.h"
#include "tempo.h"

bool VerificarRecepcaoSinal(unsigned long tempoAtual, bool &estaContando){
    if (digitalRead(PinoVT) == HIGH && !estaContando){
        digitalWrite(PinoBuzzer, HIGH);
        tempoAntigo = tempoAtual;
        tempoAntigoBuzzer = tempoAtual;
        tempoAntigoLedBranco = tempoAtual;
        estaContando = true;
      }
}

void AcionarDisjuntor(bool leituraDigitalPinoToque){
  if(leituraDigitalPinoToque){
    digitalWrite(PinoLedLaranja, HIGH); // aciona led laranja e liga o disjuntor se o sensor ativar
    digitalWrite(PinoContatora, HIGH);  // liga disjuntor
    tempoAntigoLedsLaranjaAzul = tempoAtual;
    estaContando = false;
  }
}

void DesligarDispositivos(unsigned long &tempoReferencia, int pino){
  unsigned long tempoAtual = millis();

  if(tempoAtual-tempoReferencia >=300 && digitalRead(pino)==HIGH){
    digitalWrite(pino, LOW);
    tempoReferencia = tempoAtual;
  }
}

void AcionarDispositivos(unsigned long &tempoReferencia, int valorReferenciaTempo, int pinoAcionado){
  unsigned long tempoAtual = millis();

  if(tempoAtual - tempoReferencia >= valorReferenciaTempo){
    digitalWrite(pinoAcionado, HIGH);
    tempoReferencia = tempoAtual;
  }
}

