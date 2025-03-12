#include "VT.h"
#include <Arduino.h>

ValidTransmittion::ValidTransmittion(int pino) : Entradas(pino) {
    this->estado = LOW;
    digitalWrite(this->pino, LOW);
}

void ValidTransmittion::setEstado(bool estado) {
    this->estado = estado;
}