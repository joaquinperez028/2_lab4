#ifndef DTCASA_H
#define DTCASA_H

#include <iostream>
#include "DTEspecifica.h"

using namespace std;

class DTCasa : public DTEspecifica
{
private:
    bool horizontal;

public:
    DTCasa();
    DTCasa(float Superficie, ::Direccion direccion, Fecha anioConstruc, TipoInmueble tipo, ::TipoTecho tipoTecho, bool horizontal);
    bool getHorizontal();

    friend ostream &operator<<(ostream &os, const DTCasa &dt);
};

#endif
