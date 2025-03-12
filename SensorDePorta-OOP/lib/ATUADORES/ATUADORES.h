#ifndef ATUADORES_H
#define ATUADORES_H

#include <Arduino.h>

class Atuador {
protected:
    int pino;
    bool estado;
    unsigned long tempoAntigo; // Tempo antigo para controle de intervalo
    unsigned long intervalo;  // Intervalo de tempo para controle

public:
    Atuador(int pino);
    bool getEstado();

    // Métodos virtuais puros
    virtual void ligarAtuador(unsigned long tempoAtual) = 0;
    virtual void desligarAtuador(unsigned long tempoAtual) = 0;

    // Métodos de controle de tempo
    void setTempoAntigo(unsigned long tempoAntigo);
    unsigned long getTempoDecorrido(unsigned long tempoAtual);

    // Métodos para definir e obter o intervalo
    void setIntervalo(unsigned long intervalo);
    unsigned long getIntervalo();
};

#endif