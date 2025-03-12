#ifndef LEDS_H
#define LEDS_H

#include <Arduino.h>
#include "ATUADORES.h"

class Leds : public Atuador
{
    protected:
        unsigned long tempoAntigo;
        unsigned long intervalo;

    public:
        Leds(int pino);
        void ligarAtuador(unsigned long tempoAtual, unsigned long &tempoAntigo, unsigned long intervalo) override;
        void desligarAtuador(unsigned long tempoAtual, unsigned long &tempoAntigo, unsigned long intervalo) override;
};

#endif