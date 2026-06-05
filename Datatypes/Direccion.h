#ifndef DIRECCION_H
#define DIRECCION_H

#include <iostream>
#include <string>

using namespace std;

class Direccion
{
private:
    int numPuerta;
    string calle;
    string localidad;
    string departamento;

public:
    Direccion();
    Direccion(int numPuerta, string calle, string localidad, string departamento);
    int getNumPuerta();
    string getCalle();
    string getLocalidad();
    string getDepartamento();

    friend ostream &operator<<(ostream &os, const Direccion &d);
};

#endif
