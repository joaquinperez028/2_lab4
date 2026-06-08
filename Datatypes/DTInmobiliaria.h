#ifndef DTINMOBILIARIA_H
#define DTINMOBILIARIA_H

#include <iostream>
#include <string>
#include "ICollection/interfaces/ICollectible.h"

using namespace std;

class DTInmobiliaria : public ICollectible
{
private:
    string nickname;
    string nombre;

public:
    DTInmobiliaria();
    DTInmobiliaria(string nickname, string nombre);

    string getNickname();
    string getNombre();

    friend ostream &operator<<(ostream &os, const DTInmobiliaria &dt);
};

#endif
