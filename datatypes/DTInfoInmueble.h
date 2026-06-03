#ifndef DTINFOINMUEBLE_H
#define DTINFOINMUEBLE_H

#include <iostream>
#include "Direccion.h"

class DTInfoInmueble
{
private:
    int identificador;
    direccion dir;

public:
    DTInfoInmueble(int identificador, direccion dir);
    int getIdentificador();
    direccion getDir();

    friend std::ostream &operator<<(std::ostream &os, const DTInfoInmueble &dt);
};

#endif
