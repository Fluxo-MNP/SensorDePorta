#include "ATUADORES.h"

Atuador::Atuador(int pino)
{
    this->pino = pino;
    this->estado = LOW;
    this->tempoAntigo = 0; // Inicializa o tempo antigo
    this->intervalo = 0;   // Inicializa o intervalo
    pinMode(this->pino, OUTPUT);
    digitalWrite(this->pino, LOW); // Garante que o LED comece desligado
}

bool Atuador::getEstado()
{
    return this->estado;
}

void Atuador::setTempoAntigo(unsigned long tempoAntigo)
{
    this->tempoAntigo = tempoAntigo;
}

unsigned long Atuador::getTempoDecorrido(unsigned long tempoAtual)
{
    return tempoAtual - this->tempoAntigo;
}

void Atuador::setIntervalo(unsigned long intervalo)
{
    this->intervalo = intervalo;
}

unsigned long Atuador::getIntervalo()
{
    return this->intervalo;
}

unsigned long Atuador::getDiferencaTempo(unsigned long tempoAtual){
    return tempoAtual - this->tempoAntigo; 
}