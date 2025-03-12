#include <Arduino.h>
#include "ATUADORES.h"

Atuador::Atuador(int pino)
{
    this->pino = pino;
    this->estado = LOW;
    pinMode(this->pino, OUTPUT);
}

bool Atuador::getEstado()
{
    return this->estado;
}

void trocaTempo(unsigned long &tempoAntigo, unsigned long tempoAtual)
{
    tempoAntigo = tempoAtual;
}