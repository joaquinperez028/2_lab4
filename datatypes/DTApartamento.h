#ifndef DTAPARTAMENTO_H
#define DTAPARTAMENTO_H

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
    DTApartamento(float Superficie, direccion direccion, fecha anioConstruc, tipoInmueble tipo, tipoTecho tipoTecho, int numPiso, bool ascensor, float gastosComunes);
    int getNumPiso();
    bool getAscensor();
    float getGastosComunes();
};

#endif
