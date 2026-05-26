#ifndef FECHA_H
#define FECHA_H

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
};

#endif
