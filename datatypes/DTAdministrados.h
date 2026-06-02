#ifndef DTADMINISTRADOS_H
#define DTADMINISTRADOS_H

#include "direccion.h"
#include "fecha.h"

class DTAdministrados : public ICollectible
{

private:
    fecha fechaComienzo;
    int identificador;
    direccion dir;

public:
    DTAdministrados(fecha fechaComienzo, int identificador, direccion dir);
    fecha getFechaComienzo();
    int getIdentificador();
    direccion getDir();
};

#endif