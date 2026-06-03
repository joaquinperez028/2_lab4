#include "DTInfoInmueble.h"

DTInfoInmueble ::DTInfoInmueble(int identificador, direccion dir)
{
    this->identificador = identificador;
    this->dir = dir;
}

int DTInfoInmueble ::getIdentificador()
{
    return this->identificador;
}

direccion DTInfoInmueble ::getDir()
{
    return this->dir;
}

std::ostream &operator<<(std::ostream &os, const DTInfoInmueble &dt)
{
    os << "Id: " << dt.identificador << " | Direccion: " << dt.dir;
    return os;
}
