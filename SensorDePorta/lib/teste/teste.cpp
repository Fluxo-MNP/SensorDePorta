#include "teste.h"

Atuador::Atuador(int pino, unsigned long intervalo) {
    this->pino = pino;
    this->estado = false;
    this->tempoAntigo = 0;
    this->intervalo = intervalo;
    pinMode(pino, OUTPUT);
    digitalWrite(pino, LOW);
}

void Atuador::ligar(unsigned long tempoAtual) {
    digitalWrite(pino, HIGH);
    tempoAntigo = tempoAtual;
    estado = true;
}

void Atuador::desligar(unsigned long tempoAtual) {
    digitalWrite(pino, LOW);
    tempoAntigo = tempoAtual;
    estado = false;
}

void Atuador::alternar() {
    estado = !estado;
    digitalWrite(pino, estado ? HIGH : LOW);
}

void Atuador::atualizar(unsigned long tempoAtual) {
    if (tempoAtual - tempoAntigo >= intervalo) {
        alternar();
        tempoAntigo = tempoAtual;
    }
}

bool Atuador::getEstado() {
    return estado;
}

void Atuador::atualizarComCondicao(unsigned long tempoAtual, int estadoAtual) {
    if (tempoAtual - tempoAntigo >= intervalo && digitalRead(pino) == estadoAtual) {
        digitalWrite(pino, !estadoAtual);
        tempoAntigo = tempoAtual;
    }
}