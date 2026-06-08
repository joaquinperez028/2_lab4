#include "DTInmuebleRep.h"

DTInmuebleRep::DTInmuebleRep() {}

DTInmuebleRep::DTInmuebleRep(int codigo, Direccion dir, string nombrePropietario)
{
    this->codigo = codigo;
    this->dir = dir;
    this->nombrePropietario = nombrePropietario;
}

int DTInmuebleRep::getCodigo()
{
    return this->codigo;
}

Direccion DTInmuebleRep::getDireccion()
{
    return this->dir;
}

string DTInmuebleRep::getNombrePropietario()
{
    return this->nombrePropietario;
}

ostream &operator<<(ostream &os, const DTInmuebleRep &dt)
{
    os << "Codigo: " << dt.codigo
       << " | Direccion: " << dt.dir
       << " | Propietario: " << dt.nombrePropietario;
    return os;
}
