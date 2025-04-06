#ifndef BUZZER_H
#define BUZZER_H

#include "ATUADORES.h"
class Buzzer : public Atuador
{
public:
    Buzzer(int pino);

    void ligarAtuador(unsigned long tempoAtual) override;
    void desligarAtuador(unsigned long tempoAtual) override;
};


#endif