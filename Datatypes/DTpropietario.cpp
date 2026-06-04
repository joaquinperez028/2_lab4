#include "DTpropietario.h"

DTPropietario::DTPropietario() : nickname(""), nombre("") {}

DTPropietario::DTPropietario(string nickname, string nombre)
    : nickname(nickname), nombre(nombre) {}

string DTPropietario::getNickname()
{
    return nickname;
}

string DTPropietario::getNombre()
{
    return nombre;
}

ostream &operator<<(ostream &os, const DTPropietario &dt)
{
    os << "Nickname: " << dt.nickname << " | Nombre: " << dt.nombre;
    return os;
}
