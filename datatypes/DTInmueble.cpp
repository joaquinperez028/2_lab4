#include "DTInmueble.h"

DTInmueble::DTInmueble() {}

DTInmueble::DTInmueble(int codigoInmueble, ::direccion direccion, fecha anioConstrucion, tipoInmueble tipo) {
    this->codigoInmueble = codigoInmueble;
    this->direccion_ = direccion;
    this->anioConstrucion = anioConstrucion;
    this->tipo = tipo;
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
