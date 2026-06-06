#ifndef FECHA_H
#define FECHA_H

#include <iostream>

using namespace std;

class Fecha
{
private:
    int dia;
    int mes;
    int anio;

public:
    Fecha();
    Fecha(int dia, int mes, int anio);
    int getDia();
    int getMes();
    int getAnio();
    bool operator==(const Fecha &otra) const;

    friend ostream &operator<<(ostream &os, const Fecha &f);
};

#endif
