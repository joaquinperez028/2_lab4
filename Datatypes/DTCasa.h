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
    DTCasa(float Superficie, ::direccion dir, fecha anioConstruc, tipoInmueble tipoInm, ::tipoTecho techo, bool horizontal);
    bool getHorizontal();

    friend ostream &operator<<(ostream &os, const DTCasa &dt);
};

#endif
