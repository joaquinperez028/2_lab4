#include "DTEspecifica.h"

DTEspecifica::DTEspecifica()
    : Superficie(0), direccion_(), anioConstruc(), tipo(tipoInmueble::Casa), tipoTecho_(tipoTecho::Liviano) {}

DTEspecifica::DTEspecifica(float Superficie, ::direccion direccion, fecha anioConstruc, tipoInmueble tipo, ::tipoTecho tipoTecho)
    : Superficie(Superficie), direccion_(direccion), anioConstruc(anioConstruc), tipo(tipo), tipoTecho_(tipoTecho) {}

DTEspecifica::~DTEspecifica() {}

float DTEspecifica::getSuperficie()
{
    return Superficie;
}

::direccion DTEspecifica::getDireccion()
{
    return direccion_;
}

fecha DTEspecifica::getAnioConstruc()
{
    return anioConstruc;
}

tipoInmueble DTEspecifica::getTipo()
{
    return tipo;
}

::tipoTecho DTEspecifica::getTipoTecho()
{
    return tipoTecho_;
}

ostream &operator<<(ostream &os, const DTEspecifica &dt)
{
    os << "Superficie: " << dt.Superficie
       << " | Direccion: " << dt.direccion_
       << " | Construccion: " << dt.anioConstruc
       << " | Tipo: " << dt.tipo
       << " | Techo: " << dt.tipoTecho_;
    return os;
}
