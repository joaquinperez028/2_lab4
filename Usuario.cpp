#include "Usuario.h"

Usuario::Usuario(string nickname, string nombre, string contrasenia, string email)
    : nickName(nickname), nombre(nombre), contrasenia(contrasenia), email(email)
{
}

Usuario::~Usuario()
{
}

string Usuario::getNickName()
{
    return this->nickName;
}

string Usuario::getNombre()
{
    return this->nombre;
}

string Usuario::getContrasenia()
{
    return this->contrasenia;
}

string Usuario::getEmail()
{
    return this->email;
}
