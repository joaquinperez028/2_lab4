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
    direccion direccion_;
    fecha anioConstrucion;
    tipoInmueble tipo;

public:
    DTInmueble();
    DTInmueble(int codigoInmueble, ::direccion direccion, fecha anioConstrucion, tipoInmueble tipo);

    int getCodigoInmueble();
    ::direccion getDireccion();
    fecha getAnioConstrucion();
    tipoInmueble getTipo();

    friend ostream &operator<<(ostream &os, const DTInmueble &dt);
};

#endif
