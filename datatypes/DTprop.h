#ifndef DTPROP_H
#define DTPROP_H

#include <string>
#include "Direccion.h"

using namespace std;

class DTprop
{
private:
    string cod;
    direccion direccion;
    string nombreProp;

public:
    DTprop();
    DTprop(string cod, ::direccion direccion, string nombreProp);
    string getCod();
    ::direccion getDireccion();
    string getNombreProp();
};

#endif
