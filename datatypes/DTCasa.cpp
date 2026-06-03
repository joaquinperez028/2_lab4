#include "DTCasa.h"

DTCasa::DTCasa() : DTEspecifica(), horizontal(false) {}

DTCasa::DTCasa(float Superficie, ::direccion direccion, fecha anioConstruc, tipoInmueble tipo, ::tipoTecho tipoTecho, bool horizontal)
    : DTEspecifica(Superficie, direccion, anioConstruc, tipo, tipoTecho), horizontal(horizontal) {}

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
