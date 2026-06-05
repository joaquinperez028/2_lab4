#include "DTInmueble.h"

DTInmueble::DTInmueble() {}

DTInmueble::DTInmueble(int codigoInmueble, ::direccion dir, fecha anioConstrucion, tipoInmueble tipoInm) {
    this->codigoInmueble = codigoInmueble;
    this->direccion_ = dir;
    this->anioConstrucion = anioConstrucion;
    this->tipo = tipoInm;
}

int DTInmueble::getCodigoInmueble() {
    return this->codigoInmueble;
}

direccion DTInmueble::getDireccion() {
    return this->direccion_;
}

fecha DTInmueble::getAnioConstrucion() {
    return this->anioConstrucion;
}

tipoInmueble DTInmueble::getTipo() {
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
