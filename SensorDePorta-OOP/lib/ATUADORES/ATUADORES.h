#ifndef ATUADORES_H
#define ATUADORES_H

class Atuador
{
protected:
    int pino;
    bool estado;

public:
    Atuador(int pino);
    bool getEstado();
    virtual void ligarAtuador(unsigned long tempoAtual, unsigned long &tempoAntigo, unsigned long intervalo) = 0;
    virtual void desligarAtuador(unsigned long tempoAtual, unsigned long &tempoAntigo, unsigned long intervalo) = 0;
    void trocaTempo(unsigned long &tempoAntigo, unsigned long tempoAtual);
};

#endif