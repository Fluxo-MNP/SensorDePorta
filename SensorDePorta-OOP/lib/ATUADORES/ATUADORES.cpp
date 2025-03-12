#include "ATUADORES.h"

Atuador::Atuador(int pino) {
    this->pino = pino;
    this->estado = LOW;
    this->tempoAntigo = 0; // Inicializa o tempo antigo
    this->intervalo = 0;   // Inicializa o intervalo
    pinMode(this->pino, OUTPUT);
}

bool Atuador::getEstado() {
    return this->estado;
}

void Atuador::setTempoAntigo(unsigned long tempoAntigo) {
    this->tempoAntigo = tempoAntigo;
}

unsigned long Atuador::getTempoDecorrido(unsigned long tempoAtual) {
    return tempoAtual - this->tempoAntigo;
}

void Atuador::atualizaTempo(unsigned long tempoAtual){
    this->setTempoAntigo(tempoAtual);
}

void Atuador::setIntervalo(unsigned long intervalo) {
    this->intervalo = intervalo;
}

unsigned long Atuador::getIntervalo() {
    return this->intervalo;
}