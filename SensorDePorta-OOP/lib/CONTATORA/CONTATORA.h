#ifndef CONTATORA_H
#define CONTATORA_H

#include <Arduino.h>
#include "ATUADORES.h"

class Contatora : public Atuador
{
    protected:
        unsigned long tempoAntigo;
        unsigned long intervalo;

    public:
        Contatora(int pino);
        void ligarAtuador(unsigned long tempoAtual, unsigned long &tempoAntigo, unsigned long intervalo) override;
        void desligarAtuador(unsigned long tempoAtual, unsigned long &tempoAntigo, unsigned long intervalo) override;
};

#endif