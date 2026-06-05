#ifndef DTADMINISTRADOS_H
#define DTADMINISTRADOS_H

#include <iostream>
#include "Direccion.h"
#include "Fecha.h"
#include "ICollection/interfaces/ICollectible.h"

class DTAdministrados : public ICollectible
{

private:
    Fecha fechaComienzo;
    int identificador;
    Direccion dir;

public:
    DTAdministrados(Fecha fechaComienzo, int identificador, Direccion dir);
    Fecha getFechaComienzo();
    int getIdentificador();
    Direccion getDir();

    friend std::ostream &operator<<(std::ostream &os, const DTAdministrados &dt);
};

#endif
