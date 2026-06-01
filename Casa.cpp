#include "Casa.h"
#include "Propietario.h"

Casa::Casa(direccion dir, float superficie, fecha anoConstruc, int identificador,
           tipoTecho techo, bool propHorizontal, Propietario* propietario)
    : Inmueble(dir, superficie, anoConstruc, identificador, tipoInmueble::Casa)
{
    this->techo = techo;
    this->propHorizontal = propHorizontal;
    this->propietario = propietario;
}

bool Casa::getPropHorizontal() const
{
    return this->propHorizontal;
}

tipoTecho Casa::getTipoTecho() const
{
    return this->techo;
}

void Casa::mostrarDetalle(int id)
{
    // implementar luego
}