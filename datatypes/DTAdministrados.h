#ifndef DTADMINISTRADOS_H
#define DTADMINISTRADOS_H

#include <iostream>
#include "Direccion.h"
#include "Fecha.h"
#include "ICollection/interfaces/ICollectible.h"

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

    friend std::ostream &operator<<(std::ostream &os, const DTAdministrados &dt);
};

#endif
