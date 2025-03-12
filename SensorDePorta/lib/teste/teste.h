#ifndef ATUADOR_H
#define ATUADOR_H

#include <Arduino.h>

class Atuador {
private:
    int pino;
    bool estado;
    unsigned long intervalo;
    unsigned long tempoAntigo;

public:
    Atuador(int pino, unsigned long intervalo);
    void ligar(unsigned long tempoAtual);
    void desligar(unsigned long tempoAtual);
    void alternar();
    void atualizar(unsigned long tempoAtual);
    bool getEstado();
    void atualizarComCondicao(unsigned long tempoAtual, int estadoAtual);
};

#endif
