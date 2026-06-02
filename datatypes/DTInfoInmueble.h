#ifndef DTINFOINMUEBLE_H
#define DTINFOINMUEBLE_H

#include "direccion.h"

class DTInfoInmueble
{
private:
    int identificador;
    direccion dir;

public:
    DTInfoInmueble(int identificador, direccion dir);
    int getIdentificador();
    direccion getDir();
};

#endif