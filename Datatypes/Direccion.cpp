#include "Direccion.h"

direccion::direccion() : numPuerta(0), calle(""), localidad(""), departamento("") {}

direccion::direccion(int numPuerta, string calle, string localidad, string departamento)
    : numPuerta(numPuerta), calle(calle), localidad(localidad), departamento(departamento) {}

int direccion::getNumPuerta()
{
    return numPuerta;
}

string direccion::getCalle()
{
    return calle;
}

string direccion::getLocalidad()
{
    return localidad;
}

string direccion::getDepartamento()
{
    return departamento;
}

ostream &operator<<(ostream &os, const direccion &d)
{
    os << d.calle << " " << d.numPuerta << ", " << d.localidad << " (" << d.departamento << ")";
    return os;
}
