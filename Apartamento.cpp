#include "Apartamento.h"

Apartamento::Apartamento(direccion dir, float superficie, int identificador, int numPiso, bool ascensor, float gastosComunes)
    : Inmueble(dir, superficie, fecha(), identificador, tipoInmueble::Apartamento),
      numPiso(numPiso),
      ascensor(ascensor),
      gastosComunes(gastosComunes)
{
}

int Apartamento::getNumPiso() const
{
    return numPiso;
}

bool Apartamento::getAscensor() const
{
    return ascensor;
}

float Apartamento::getGastosComunes() const
{
    return gastosComunes;
}

void Apartamento::crearApto(direccion, float, int, int, bool, float)
{
}

void Apartamento::mostrarDetalle(int)
{
}
