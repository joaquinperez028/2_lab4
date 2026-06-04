#include "Fecha.h"

fecha::fecha() : dia(0), mes(0), anio(0) {}

fecha::fecha(int dia, int mes, int anio) : dia(dia), mes(mes), anio(anio) {}

int fecha::getDia()
{
    return dia;
}

int fecha::getMes()
{
    return mes;
}

int fecha::getAnio()
{
    return anio;
}

bool fecha ::operator==(const fecha &otra) const
{
    return dia == otra.dia &&
           mes == otra.mes &&
           anio == otra.anio;
}

ostream &operator<<(ostream &os, const fecha &f)
{
    os << f.dia << "/" << f.mes << "/" << f.anio;
    return os;
}
