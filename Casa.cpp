#include "Casa.h"
#include "Propietario.h"

Casa::Casa(Direccion dir, float superficie, Fecha anoConstruc, int identificador,
           TipoTecho techo, bool propHorizontal, Propietario *propietario)
    : Inmueble(dir, superficie, anoConstruc, identificador, TipoInmueble::Casa),
      techo(techo),
      propHorizontal(propHorizontal)
{
    if (propietario != nullptr)
    {
        asociarPropietario(propietario);
    }
}

bool Casa::getPropHorizontal() const
{
    return propHorizontal;
}

TipoTecho Casa::getTipoTecho() const
{
    return techo;
}

void Casa::mostrarDetalle(int)
{
}

DTEspecifica *Casa::getInmueble()
{
    return new DTCasa(
        getSuperficie(),
        getDireccion(),
        getAnoConstruc(),
        TipoInmueble::Casa,
        techo,
        propHorizontal);
}
