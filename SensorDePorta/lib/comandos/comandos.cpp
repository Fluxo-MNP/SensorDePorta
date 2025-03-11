#include <Arduino.h>
#include "comandos.h"
#include "tempo.h"

bool VerificarRecepcaoSinal(unsigned long tempoAtual, bool estaContando){
    if (digitalRead(PinoVT) == HIGH && !estaContando){
        digitalWrite(PinoBuzzer, HIGH);
        tempoAntigo = tempoAtual;
        tempoAntigoBuzzer = tempoAtual;
        tempoAntigoLedBranco = tempoAtual;
        return true;
      }
      return false;
}
