#include "DTApartamento.h"

DTApartamento::DTApartamento() : DTEspecifica(), numPiso(0), ascensor(false), gastosComunes(0) {}

DTApartamento::DTApartamento(float Superficie, ::direccion dir, fecha anioConstruc, tipoInmueble tipoInm, ::tipoTecho techo, int numPiso, bool ascensor, float gastosComunes)
    : DTEspecifica(Superficie, dir, anioConstruc, tipoInm, techo), numPiso(numPiso), ascensor(ascensor), gastosComunes(gastosComunes) {}

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
