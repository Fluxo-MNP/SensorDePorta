#ifndef ENTRADAS_H
#define ENTRADAS_H

#include <Arduino.h>

class Entradas {
protected:
    int pino;
    bool estado;

public:
    Entradas(int pino);
    bool getEstado();
};

#endif