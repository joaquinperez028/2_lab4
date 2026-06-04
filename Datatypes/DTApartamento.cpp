#include "DTApartamento.h"

DTApartamento::DTApartamento() : DTEspecifica(), numPiso(0), ascensor(false), gastosComunes(0) {}

DTApartamento::DTApartamento(float Superficie, ::direccion direccion, fecha anioConstruc, tipoInmueble tipo, ::tipoTecho tipoTecho, int numPiso, bool ascensor, float gastosComunes)
    : DTEspecifica(Superficie, direccion, anioConstruc, tipo, tipoTecho), numPiso(numPiso), ascensor(ascensor), gastosComunes(gastosComunes) {}

int DTApartamento::getNumPiso()
{
    return numPiso;
}

bool DTApartamento::getAscensor()
{
    return ascensor;
}

float DTApartamento::getGastosComunes()
{
    return gastosComunes;
}

ostream &operator<<(ostream &os, const DTApartamento &dt)
{
    os << static_cast<const DTEspecifica &>(dt)
       << " | Piso: " << dt.numPiso
       << " | Ascensor: " << (dt.ascensor ? "Si" : "No")
       << " | Gastos comunes: " << dt.gastosComunes;
    return os;
}
