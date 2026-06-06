#include "DTInfoInmueble.h"

DTInfoInmueble ::DTInfoInmueble(int identificador, Direccion dir)
{
    this->identificador = identificador;
    this->dir = dir;
}

int DTInfoInmueble ::getIdentificador()
{
    return this->identificador;
}

Direccion DTInfoInmueble ::getDir()
{
    return this->dir;
}

std::ostream &operator<<(std::ostream &os, const DTInfoInmueble &dt)
{
    os << "Id: " << dt.identificador << " | Direccion: " << dt.dir;
    return os;
}
