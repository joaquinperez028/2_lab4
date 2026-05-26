#ifndef DIRECCION_H
#define DIRECCION_H

#include <string>

using namespace std;

class direccion
{
private:
    int numPuerta;
    string calle;
    string localidad;
    string departamento;

public:
    direccion();
    direccion(int numPuerta, string calle, string localidad, string departamento);
    int getNumPuerta();
    string getCalle();
    string getLocalidad();
    string getDepartamento();
};

#endif
