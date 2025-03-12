#ifndef VT_H
#define VT_H

#include "ENTRADAS.h"

class ValidTransmittion : public Entradas {
public:
    ValidTransmittion(int pino);
    void setEstado(bool estado);
};

#endif