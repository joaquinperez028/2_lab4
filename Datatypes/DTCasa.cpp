#include "DTCasa.h"

DTCasa::DTCasa() : DTEspecifica(), horizontal(false) {}

DTCasa::DTCasa(float Superficie, ::direccion dir, fecha anioConstruc, tipoInmueble tipoInm, ::tipoTecho techo, bool horizontal)
    : DTEspecifica(Superficie, dir, anioConstruc, tipoInm, techo), horizontal(horizontal) {}

bool DTCasa::getHorizontal()
{
    return horizontal;
}

ostream &operator<<(ostream &os, const DTCasa &dt)
{
    os << static_cast<const DTEspecifica &>(dt)
       << " | Horizontal: " << (dt.horizontal ? "Si" : "No");
    return os;
}
