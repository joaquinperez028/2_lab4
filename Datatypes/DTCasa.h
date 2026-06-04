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
    DTCasa(float Superficie, ::direccion direccion, fecha anioConstruc, tipoInmueble tipo, ::tipoTecho tipoTecho, bool horizontal);
    bool getHorizontal();

    friend ostream &operator<<(ostream &os, const DTCasa &dt);
};

#endif
