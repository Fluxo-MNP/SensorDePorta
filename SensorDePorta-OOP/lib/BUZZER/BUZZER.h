#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>
#include "ATUADORES.h"

class Buzzer : public Atuador
{
private:
    unsigned long tempoAntigo;
    unsigned long intervalo;

public:
    Buzzer(int pino);
    void ligarAtuador(unsigned long tempoAtual, unsigned long &tempoAntigo, unsigned long intervalo) override;
    void desligarAtuador(unsigned long tempoAtual, unsigned long &tempoAntigo, unsigned long intervalo) override;
};

#endif