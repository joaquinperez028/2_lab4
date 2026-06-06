#include "DTPropiedad.h"

DTPropiedad::DTPropiedad() {}

DTPropiedad::DTPropiedad(int identificador, Direccion dir, Fecha anioConstrucion,
                         string nombrePropietario)
{
    this->identificador = identificador;
    this->dir = dir;
    this->anioConstrucion = anioConstrucion;
    this->nombrePropietario = nombrePropietario;
}

int DTPropiedad::getIdentificador()
{
    return this->identificador;
}

Direccion DTPropiedad::getDireccion()
{
    return this->dir;
}

Fecha DTPropiedad::getAnioConstrucion()
{
    return this->anioConstrucion;
}

string DTPropiedad::getNombrePropietario()
{
    return this->nombrePropietario;
}

ostream &operator<<(ostream &os, const DTPropiedad &dt)
{
    os << "Codigo: " << dt.identificador
       << " | Direccion: " << dt.dir
       << " | Propietario: " << dt.nombrePropietario;
    return os;
}
