#ifndef LEDS_H
#define LEDS_H

#include <Arduino.h>
#include "ATUADORES.h"

class Leds : public Atuador {
public:
    Leds(int pino);

    void ligarAtuador(unsigned long tempoAtual) override;
    void desligarAtuador(unsigned long tempoAtual) override;
};

#endif