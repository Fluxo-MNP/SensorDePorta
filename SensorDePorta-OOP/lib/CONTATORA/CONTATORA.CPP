#include "CONTATORA.h"

Contatora::Contatora(int pino) : Atuador(pino) {}

void Contatora::ligarAtuador(unsigned long tempoAtual) {
    this->estado = HIGH;
    digitalWrite(this->pino, this->estado);
}

void Contatora::desligarAtuador(unsigned long tempoAtual) {
    this->estado = LOW;
    digitalWrite(this->pino, this->estado);
}