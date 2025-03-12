#include <Arduino.h>
#include "ATUADORES.h"
#include "CONTATORA.h"

Contatora::Contatora(int pino):Atuador(pino){
    this->tempoAntigo = 0;
    this->intervalo = 0;
}

void Contatora::ligarAtuador(unsigned long tempoAtual, unsigned long &tempoAntigo, unsigned long intervalo){
    this->estado = HIGH;
    digitalWrite(this->pino, this->estado);
}

void Contatora::desligarAtuador(unsigned long tempoAtual, unsigned long &tempoAntigo, unsigned long intervalo){
    this->estado = LOW;
    digitalWrite(this->pino, this->estado);
}
