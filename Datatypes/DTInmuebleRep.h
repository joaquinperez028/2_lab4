#ifndef DTINMUEBLEREP_H
#define DTINMUEBLEREP_H

#include <iostream>
#include <string>
#include "Direccion.h"
#include "ICollection/interfaces/ICollectible.h"

using namespace std;

class DTInmuebleRep : public ICollectible
{
private:
    int codigo;
    Direccion dir;
    string nombrePropietario;

public:
    DTInmuebleRep();
    DTInmuebleRep(int codigo, Direccion dir, string nombrePropietario);

    int getCodigo();
    Direccion getDireccion();
    string getNombrePropietario();

    friend ostream &operator<<(ostream &os, const DTInmuebleRep &dt);
};

#endif
