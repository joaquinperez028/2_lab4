#include "Casa.h"

Casa::Casa(direccion dir, float superficie, int identificador, tipoTecho techo, bool propHorizontal)
    : Inmueble(dir, superficie, fecha(), identificador, tipoInmueble::Casa),
      techo(techo),
      propHorizontal(propHorizontal)
{
}

bool Casa::getPropHorizontal() const
{
    return propHorizontal;
}

tipoTecho Casa::getTipoTecho() const
{
    return techo;
}

void Casa::crearCasa(direccion, float, int, tipoTecho, bool)
{
}

void Casa::mostrarDetalle(int)
{
}
