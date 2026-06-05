#ifndef DTINFOINMUEBLE_H
#define DTINFOINMUEBLE_H

#include <iostream>
#include "Direccion.h"

class DTInfoInmueble
{
private:
    int identificador;
    Direccion dir;

public:
    DTInfoInmueble(int identificador, Direccion dir);
    int getIdentificador();
    Direccion getDir();

    friend std::ostream &operator<<(std::ostream &os, const DTInfoInmueble &dt);
};

#endif
