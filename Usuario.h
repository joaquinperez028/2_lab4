#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include "ICollection/interfaces/ICollectible.h"

using namespace std;

class Usuario : public ICollectible
{
protected:
    string nickName;
    string nombre;
    string contrasenia;
    string email;

public:
    Usuario(string nickname, string nombre, string contrasenia, string email);
    virtual ~Usuario();
    string getNickName();
    string getNombre();
    string getContrasenia();
    string getEmail();
};

#endif
