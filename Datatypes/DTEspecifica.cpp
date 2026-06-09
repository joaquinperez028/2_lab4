#include "DTEspecifica.h"

DTEspecifica::DTEspecifica()
    : Superficie(0), direccion(), anioConstruc(), tipo(TipoInmueble::Casa), tipoTecho(TipoTecho::Liviano) {}

DTEspecifica::DTEspecifica(float Superficie, ::Direccion direccion, Fecha anioConstruc, TipoInmueble tipo, ::TipoTecho tipoTecho)
    : Superficie(Superficie), direccion(direccion), anioConstruc(anioConstruc), tipo(tipo), tipoTecho(tipoTecho) {}

DTEspecifica::~DTEspecifica() {}

float DTEspecifica::getSuperficie()
{
    return Superficie;
}

::Direccion DTEspecifica::getDireccion()
{
    return direccion;
}

Fecha DTEspecifica::getAnioConstruc()
{
    return anioConstruc;
}

TipoInmueble DTEspecifica::getTipo()
{
    return tipo;
}

::TipoTecho DTEspecifica::getTipoTecho()
{
    return tipoTecho;
}

ostream &operator<<(ostream &os, const DTEspecifica &dt)
{
    os << "Superficie: " << dt.Superficie
       << " | Direccion: " << dt.direccion
       << " | Construccion: " << dt.anioConstruc
       << " | Tipo: " << dt.tipo;

    if (dt.tipo == TipoInmueble::Casa)
        os << " | Techo: " << dt.tipoTecho;

    return os;
}
