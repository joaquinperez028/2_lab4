#ifndef USUARIO_H
#define USUARIO_H

#include "ICollection.h"
#include "ICollectible.h"
#include "string"

using namespace std;

class Usuario : public ICollectible {
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
        Status revisarNickname(string);
        DTInmobiliaria listarInmobiliarias();
        DTprop listarPropietarios();
        DTInmuebles seleccionarInmobiliaria(string);

};

#endif

