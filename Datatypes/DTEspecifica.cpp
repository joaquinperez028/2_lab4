#include "DTEspecifica.h"

DTEspecifica::DTEspecifica()
    : Superficie(0), direccion(), anioConstruc(), tipo(tipoInmueble::Casa), tipoTecho(tipoTecho::Liviano) {}

DTEspecifica::DTEspecifica(float Superficie, ::direccion direccion, fecha anioConstruc, tipoInmueble tipo, ::tipoTecho tipoTecho)
    : Superficie(Superficie), direccion(direccion), anioConstruc(anioConstruc), tipo(tipo), tipoTecho(tipoTecho) {}

DTEspecifica::~DTEspecifica() {}

float DTEspecifica::getSuperficie()
{
    return Superficie;
}

::direccion DTEspecifica::getDireccion()
{
    return direccion;
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
    return tipoTecho;
}

ostream &operator<<(ostream &os, const DTEspecifica &dt)
{
    os << "Superficie: " << dt.Superficie
       << " | Direccion: " << dt.direccion
       << " | Construccion: " << dt.anioConstruc
       << " | Tipo: " << dt.tipo
       << " | Techo: " << dt.tipoTecho;
    return os;
}
