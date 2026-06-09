#ifndef DTESPECIFICA_H
#define DTESPECIFICA_H

#include <iostream>
#include "Direccion.h"
#include "Fecha.h"
#include "TipoInmueble.h"
#include "TipoTecho.h"

using namespace std;

class DTEspecifica
{
protected:
    float Superficie;
    Direccion direccion;
    Fecha anioConstruc;
    TipoInmueble tipo;
    TipoTecho tipoTecho;

public:
    DTEspecifica();
    DTEspecifica(float Superficie, ::Direccion direccion, Fecha anioConstruc, TipoInmueble tipo);
    DTEspecifica(float Superficie, ::Direccion direccion, Fecha anioConstruc, TipoInmueble tipo, ::TipoTecho tipoTecho);
    virtual ~DTEspecifica();
    float getSuperficie();
    ::Direccion getDireccion();
    Fecha getAnioConstruc();
    TipoInmueble getTipo();
    ::TipoTecho getTipoTecho();

    friend ostream &operator<<(ostream &os, const DTEspecifica &dt);
};

#endif
