#include "Fecha.h"

Fecha::Fecha() : dia(0), mes(0), anio(0) {}

Fecha::Fecha(int dia, int mes, int anio) : dia(dia), mes(mes), anio(anio) {}

int Fecha::getDia()
{
    return dia;
}

int Fecha::getMes()
{
    return mes;
}

int Fecha::getAnio()
{
    return anio;
}

bool Fecha ::operator==(const Fecha &otra) const
{
    return dia == otra.dia &&
           mes == otra.mes &&
           anio == otra.anio;
}

ostream &operator<<(ostream &os, const Fecha &f)
{
    os << f.dia << "/" << f.mes << "/" << f.anio;
    return os;
}
