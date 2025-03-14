#ifndef CONTATORA_H
#define CONTATORA_H

#include <Arduino.h>
#include "ATUADORES.h"

class Contatora : public Atuador
{
public:
    Contatora(int pino);
    void ligarAtuador(unsigned long tempoAtual) override;
    void desligarAtuador(unsigned long tempoAtual) override;
};


#endif