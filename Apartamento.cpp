#include "Apartamento.h"
#include "Propietario.h"

Apartamento::Apartamento(direccion dir, float superficie, fecha anoConstruc, int identificador,
                         int numPiso, bool ascensor, float gastosComunes, Propietario* propietario)
    : Inmueble(dir, superficie, anoConstruc, identificador, tipoInmueble::Apartamento)
{
    this->numPiso = numPiso;
    this->ascensor = ascensor;
    this->gastosComunes = gastosComunes;
    this->propietario = propietario;
}

int Apartamento::getNumPiso() const
{
    return this->numPiso;
}

bool Apartamento::getAscensor() const
{
    return this->ascensor;
}

float Apartamento::getGastosComunes() const
{
    return this->gastosComunes;
}

void Apartamento::mostrarDetalle(int id)
{
    // implementar luego
}