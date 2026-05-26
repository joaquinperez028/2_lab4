#ifndef DTESPECIFICA_H
#define DTESPECIFICA_H

#include "direccion.h"
#include "fecha.h"
#include "tipoInmueble.h"
#include "tipoTecho.h"

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
    DTEspecifica(float Superficie, direccion direccion, fecha anioConstruc, tipoInmueble tipo, tipoTecho tipoTecho);
    virtual ~DTEspecifica();
    float getSuperficie();
    direccion getDireccion();
    fecha getAnioConstruc();
    tipoInmueble getTipo();
    tipoTecho getTipoTecho();
};

#endif
