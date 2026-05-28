#ifndef CLIENTE_H
#define CLIENTE_H

#include "Usuario.h"
#include <string>

using namespace std;

class Cliente : public Usuario
{
private:
    string apellido;
    string documento;

public:
    Cliente(string nickname, string nombre, string contrasenia, string email, string apellido, string documento);
    ~Cliente();

    string getApellido();
    string getDocumento();
};

#endif
