#ifndef ENTRADAS_H
#define ENTRADAS_H
class Entradas
{
protected:
    int pino;
    bool estado;

public:
    Entradas(int pino);
    bool getEstado();
};
#endif