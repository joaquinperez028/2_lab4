#include "DTEspecifica.h"

DTEspecifica::DTEspecifica()
    : Superficie(0), direccion_(), anioConstruc(), tipoInmueble_(tipoInmueble::Casa), techo_(tipoTecho::Liviano) {}

DTEspecifica::DTEspecifica(float Superficie, ::direccion dir, fecha anioConstruc, tipoInmueble tipoInm, ::tipoTecho techo)
    : Superficie(Superficie), direccion_(dir), anioConstruc(anioConstruc), tipoInmueble_(tipoInm), techo_(techo) {}

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
    return tipoInmueble_;
}

::tipoTecho DTEspecifica::getTipoTecho()
{
    return techo_;
}

ostream &operator<<(ostream &os, const DTEspecifica &dt)
{
    os << "Superficie: " << dt.Superficie
       << " | Direccion: " << dt.direccion_
       << " | Construccion: " << dt.anioConstruc
       << " | Tipo: " << dt.tipoInmueble_
       << " | Techo: " << dt.techo_;
    return os;
}
