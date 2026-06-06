#include "DTInmueble.h"

DTInmueble::DTInmueble() {}

DTInmueble::DTInmueble(int codigoInmueble, ::Direccion direccion, Fecha anioConstrucion, TipoInmueble tipo,
                       string nombrePropietario)
{
    this->codigoInmueble = codigoInmueble;
    this->direccion_ = direccion;
    this->anioConstrucion = anioConstrucion;
    this->tipo = tipo;
    this->nombrePropietario = nombrePropietario;
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

string DTInmueble::getNombrePropietario()
{
    return this->nombrePropietario;
}

ostream &operator<<(ostream &os, const DTInmueble &dt)
{
    os << "Codigo: " << dt.codigoInmueble
       << " | Direccion: " << dt.direccion_
       << " | Propietario: " << dt.nombrePropietario
       << " | Construccion: " << dt.anioConstrucion
       << " | Tipo: " << dt.tipo;
    return os;
}
