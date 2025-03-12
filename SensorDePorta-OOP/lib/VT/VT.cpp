#include <Arduino.h>
#include "VT.h"
#include "ENTRADA.h"

ValidTransmittion::ValidTransmittion(int pino):Entradas(pino){
    this->estado = 0;
    digitalWrite(this->pino, LOW);
}