#ifndef DTPROPIETARIO_H
#define DTPROPIETARIO_H

#include <iostream>
#include <string>
#include "ICollection/interfaces/ICollectible.h"

using namespace std;

class DTPropietario : public ICollectible
{
private:
    string nickname;
    string nombre;

public:
    DTPropietario();
    DTPropietario(string nickname, string nombre);
    string getNickname();
    string getNombre();

    friend ostream &operator<<(ostream &os, const DTPropietario &dt);
};

#endif
