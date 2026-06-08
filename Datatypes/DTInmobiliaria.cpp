#include "DTInmobiliaria.h"

DTInmobiliaria::DTInmobiliaria() : nickname(""), nombre("") {}

DTInmobiliaria::DTInmobiliaria(string nickname, string nombre)
    : nickname(nickname), nombre(nombre) {}

string DTInmobiliaria::getNickname()
{
    return this->nickname;
}

string DTInmobiliaria::getNombre()
{
    return this->nombre;
}

ostream &operator<<(ostream &os, const DTInmobiliaria &dt)
{
    os << "Nickname: " << dt.nickname << " | Nombre: " << dt.nombre;
    return os;
}
