#include "Direccion.h"

Direccion::Direccion() : numPuerta(0), calle(""), localidad(""), departamento("") {}

Direccion::Direccion(int numPuerta, string calle, string localidad, string departamento)
    : numPuerta(numPuerta), calle(calle), localidad(localidad), departamento(departamento) {}

int Direccion::getNumPuerta()
{
    return numPuerta;
}

string Direccion::getCalle()
{
    return calle;
}

string Direccion::getLocalidad()
{
    return localidad;
}

string Direccion::getDepartamento()
{
    return departamento;
}

ostream &operator<<(ostream &os, const Direccion &d)
{
    os << d.calle << " " << d.numPuerta << ", " << d.localidad << " (" << d.departamento << ")";
    return os;
}
