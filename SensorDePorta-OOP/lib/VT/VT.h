#ifndef VT_H
#define VT_H

#include "ENTRADA.h"

class ValidTransmittion : public Entradas
{
    public:
    
        ValidTransmittion(int pino);
        void setEstado(bool estado);

};

#endif