#include "DTInmueble.h"

DTInmueble::DTInmueble() {}

DTInmueble::DTInmueble(int codigoInmueble, ::Direccion direccion, Fecha anioConstrucion, TipoInmueble tipo)
{
    this->codigoInmueble = codigoInmueble;
    this->direccion_ = direccion;
    this->anioConstrucion = anioConstrucion;
    this->tipo = tipo;
}

int DTInmueble::getCodigoInmueble()
{
    return this->codigoInmueble;
}

Direccion DTInmueble::getDireccion()
{
    return this->direccion_;
}

Fecha DTInmueble::getAnioConstrucion()
{
    return this->anioConstrucion;
}

TipoInmueble DTInmueble::getTipo()
{
    return this->tipo;
}

ostream &operator<<(ostream &os, const DTInmueble &dt)
{
    os << "Codigo: " << dt.codigoInmueble
       << " | Direccion: " << dt.direccion_
       << " | Construccion: " << dt.anioConstrucion
       << " | Tipo: " << dt.tipo;
    return os;
}
