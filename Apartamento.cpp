#include "Apartamento.h"
#include "Propietario.h"

Apartamento::Apartamento(direccion dir, float superficie, fecha anoConstruc, int identificador,
                         int numPiso, bool ascensor, float gastosComunes, Propietario *propietario)
    : Inmueble(dir, superficie, anoConstruc, identificador, tipoInmueble::Apartamento),
      numPiso(numPiso),
      ascensor(ascensor),
      gastosComunes(gastosComunes)
{
    if (propietario != nullptr)
    {
        asociarPropietario(propietario);
    }
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

void Apartamento::mostrarDetalle(int)
{
}

DTEspecifica *Apartamento::getInmueble()
{
    return new DTApartamento(
        getSuperficie(),
        getDireccion(),
        getAnoConstruc(),
        tipoInmueble::Apartamento,
        tipoTecho::Liviano,
        numPiso,
        ascensor,
        gastosComunes);
}
