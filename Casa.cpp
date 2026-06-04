#include "Casa.h"
#include "Propietario.h"

Casa::Casa(direccion dir, float superficie, fecha anoConstruc, int identificador,
           tipoTecho techo, bool propHorizontal, Propietario *propietario)
    : Inmueble(dir, superficie, anoConstruc, identificador, tipoInmueble::Casa),
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

tipoTecho Casa::getTipoTecho() const
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
        tipoInmueble::Casa,
        techo,
        propHorizontal);
}
