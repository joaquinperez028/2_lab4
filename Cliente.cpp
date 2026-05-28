#include "Cliente.h"

Cliente::Cliente(string nickname, string nombre, string contrasenia, string email, string apellido, string documento)
    : Usuario(nickname, nombre, contrasenia, email), apellido(apellido), documento(documento)
{
}

Cliente::~Cliente()
{
}

string Cliente::getApellido()
{
    return this->apellido;
}

string Cliente::getDocumento()
{
    return this->documento;
}
