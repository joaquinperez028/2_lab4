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
    direccion direccion;
    fecha anioConstruc;
    tipoInmueble tipo;
    tipoTecho tipoTecho;

public:
    DTEspecifica();
    DTEspecifica(float Superficie, ::direccion direccion, fecha anioConstruc, tipoInmueble tipo, ::tipoTecho tipoTecho);
    virtual ~DTEspecifica();
    float getSuperficie();
    ::direccion getDireccion();
    fecha getAnioConstruc();
    tipoInmueble getTipo();
    ::tipoTecho getTipoTecho();

    friend ostream &operator<<(ostream &os, const DTEspecifica &dt);
};

#endif
