#ifndef PROPIETARIO_H
#define PROPIETARIO_H

#include "Usuario.h"
#include "Inmueble.h"
#include "ColInmueble.h"
#include "ICollection.h"
#include "ICollectible.h"

using namespace std;

class Inmueble; 
class Inmobiliaria;

class Propietario : public Usuario {
    protected:
        string numCuenta;
        string banco;
        string telefono;
        ColInmueble* inmuebles; //UTILIZO EL WRAPPER CREADO EN SISTEMA PARA LA COLECCION DE INMUEBLES, ESTO ES PARA NAVEGAR A INMUEBLE
        Inmobiliaria* inmo; //PUNTERO A LA INMOBILIARIA CONCRETA, PARA PODER COMUNICARME

    public:
        Propietario(string numCuenta, string banco, string telefono);
        ~Propietario();
        string getNumCuenta();
        string getBanco();
        string getTelefono();
        void removerPropietario(Inmueble*); //ESTA BIEN USAR * ?? O DEBO USAR & ??
        Status altaCasa(direccion, float, int, tipoTecho, bool);
        Status altaApto(direccion, float, int, int, bool, float);

};

#endif