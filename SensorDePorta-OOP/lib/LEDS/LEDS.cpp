#include <Arduino.h>
#include "LEDS.h"

Leds::Leds(int pino):Atuador(pino){
    this->tempoAntigo = 0;
    this->intervalo = 0;
}

void Leds::ligarAtuador(unsigned long tempoAtual, unsigned long &tempoAntigo, unsigned long intervalo){
    unsigned long tempoDecorrido = tempoAtual - tempoAntigo;

    if (tempoDecorrido >= intervalo && this->getEstado() == LOW) {
        this->estado = HIGH;
        digitalWrite(this->pino, this->estado);
        tempoAntigo = tempoAtual;
    }
}

void Leds::desligarAtuador(unsigned long tempoAtual, unsigned long &tempoAntigo, unsigned long intervalo){
    unsigned long tempoDecorrido = tempoAtual - tempoAntigo;

    if (tempoDecorrido >= intervalo && this->getEstado() == LOW) {
        this->estado = HIGH;
        digitalWrite(this->pino, this->estado);
        tempoAntigo = tempoAtual;
    }
}