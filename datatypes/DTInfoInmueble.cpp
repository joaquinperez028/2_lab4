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
