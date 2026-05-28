#ifndef PROPIETARIO_H
#define PROPIETARIO_H

#include "Usuario.h"
#include "Datatypes/Direccion.h"
#include "Datatypes/TipoTecho.h"
#include "Datatypes/Status.h"

using namespace std;

class Inmueble;
class Inmobiliaria;
class ColInmueble;

class Propietario : public Usuario {
    protected:
        string numCuenta;
        string banco;
        string telefono;
        ColInmueble* inmuebles;
        Inmobiliaria* inmo;

    public:
        Propietario(string nickname, string nombre, string contrasenia, string email,
                    string numCuenta, string banco, string telefono);
        ~Propietario();
        string getNumCuenta();
        string getBanco();
        string getTelefono();
        void asociarInmobiliaria(Inmobiliaria* inmobiliaria);
        void removerPropietario(Inmueble*); //ESTA BIEN USAR * ?? O DEBO USAR & ??
        Status altaCasa(direccion, float, int, tipoTecho, bool);
        Status altaApto(direccion, float, int, int, bool, float);

};

#endif