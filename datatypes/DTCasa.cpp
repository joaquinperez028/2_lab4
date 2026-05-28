#include "DTCasa.h"

DTCasa::DTCasa() : DTEspecifica(), horizontal(false) {}

DTCasa::DTCasa(float Superficie, ::direccion direccion, fecha anioConstruc, tipoInmueble tipo, ::tipoTecho tipoTecho, bool horizontal)
    : DTEspecifica(Superficie, direccion, anioConstruc, tipo, tipoTecho), horizontal(horizontal) {}

bool DTCasa::getHorizontal()
{
    return horizontal;
}
