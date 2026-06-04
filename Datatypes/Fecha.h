#ifndef FECHA_H
#define FECHA_H

#include <iostream>

using namespace std;

class fecha
{
private:
    int dia;
    int mes;
    int anio;

public:
    fecha();
    fecha(int dia, int mes, int anio);
    int getDia();
    int getMes();
    int getAnio();
    bool operator==(const fecha &otra) const;

    friend ostream &operator<<(ostream &os, const fecha &f);
};

#endif
