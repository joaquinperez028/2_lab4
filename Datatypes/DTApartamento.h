#ifndef DTAPARTAMENTO_H
#define DTAPARTAMENTO_H

#include <iostream>
#include "DTEspecifica.h"

using namespace std;

class DTApartamento : public DTEspecifica
{
private:
    int numPiso;
    bool ascensor;
    float gastosComunes;

public:
    DTApartamento();
    DTApartamento(float Superficie, ::Direccion direccion, Fecha anioConstruc, TipoInmueble tipo, int numPiso, bool ascensor, float gastosComunes);
    int getNumPiso();
    bool getAscensor();
    float getGastosComunes();

    friend ostream &operator<<(ostream &os, const DTApartamento &dt);
};

#endif
