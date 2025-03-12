#include "ENTRADAS.h"
#include <Arduino.h>

Entradas::Entradas(int pino)
{
    this->pino = pino;
    pinMode(pino, INPUT);
}

bool Entradas::getEstado()
{
    this->estado = digitalRead(this->pino);
    return this->estado;
}