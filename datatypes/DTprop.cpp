#include "DTprop.h"

DTprop::DTprop() : cod(""), direccion(), nombreProp("") {}

DTprop::DTprop(string cod, ::direccion direccion, string nombreProp)
    : cod(cod), direccion(direccion), nombreProp(nombreProp) {}

string DTprop::getCod()
{
    return cod;
}

::direccion DTprop::getDireccion()
{
    return direccion;
}

string DTprop::getNombreProp()
{
    return nombreProp;
}
