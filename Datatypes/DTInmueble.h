#ifndef DTINMUEBLE_H
#define DTINMUEBLE_H

#include <iostream>
#include "Direccion.h"
#include "Fecha.h"
#include "TipoInmueble.h"
#include "ICollection/interfaces/ICollectible.h"

using namespace std;

class DTInmueble : public ICollectible
{
private:
    int codigoInmueble;
    Direccion direccion_;
    Fecha anioConstrucion;
    TipoInmueble tipo;

public:
    DTInmueble();
    DTInmueble(int codigoInmueble, ::Direccion direccion, Fecha anioConstrucion, TipoInmueble tipo);

    int getCodigoInmueble();
    ::Direccion getDireccion();
    Fecha getAnioConstrucion();
    TipoInmueble getTipo();

    friend ostream &operator<<(ostream &os, const DTInmueble &dt);
};

#endif
