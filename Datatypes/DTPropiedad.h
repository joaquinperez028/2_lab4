#ifndef DTPROPIEDAD_H
#define DTPROPIEDAD_H

#include <iostream>
#include <string>
#include "Direccion.h"
#include "Fecha.h"
#include "ICollection/interfaces/ICollectible.h"

using namespace std;

class DTPropiedad : public ICollectible
{
private:
    string nombrePropietario;
    int identificador;
    Direccion dir;
    Fecha anioConstrucion;

public:
    DTPropiedad();
    DTPropiedad(int identificador, Direccion dir, Fecha anioConstrucion, string nombrePropietario);

    int getIdentificador();
    Direccion getDireccion();
    Fecha getAnioConstrucion();
    string getNombrePropietario();

    friend ostream &operator<<(ostream &os, const DTPropiedad &dt);
};

#endif
