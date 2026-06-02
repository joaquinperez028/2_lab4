#ifndef PROPIETARIO_H
#define PROPIETARIO_H

#include "Usuario.h"
#include "Datatypes/Direccion.h"
#include "Datatypes/TipoTecho.h"
#include "Datatypes/Status.h"
#include "ICollection.h"
#include "ICollection/interfaces/IDictionary.h"

using namespace std;

class Inmueble;
class Inmobiliaria;
class Casa;
class Apartamento;

class Propietario : public Usuario {
    protected:
        string numCuenta;
        string banco;
        string telefono;
        IDictionary* inmuebles;
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
        Casa* crearCasa(direccion, float, fecha, int, tipoTecho, bool);
        Apartamento* crearApto(direccion, float, fecha, int, int, bool, float); //cambiar en diagrama de comunicacion

};

#endif