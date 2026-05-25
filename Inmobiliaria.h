#ifndef INMOBILIARIA_H
#define INMOBILIARIA_H

#include "Usuario.h"
#include "Inmueble.h"
#include "ColInmueble.h"
#include "Administra.h"
#include "ColAdministra.h"

class Usuario;
class Propietario;
class Inmueble;
class Administra;

class Inmobiliaria : public Usuario{
    protected:
        direccion direccion;
        string telefono;
        string URL;
        ColInmueble* inmuebles;
        ColAdministra* administraciones;

    public:
        Inmobiliaria(direccion direccion, string telefono, string URL);
        ~Inmobiliaria();
        direccion getDireccion();
        string getTelefono();
        string getUrl();
        void asociarPropietario(Propietario* propietario);
        Status crearAdministra(Int); //para chequear en el diagrama de comunicacion si devuelve status
        void removerInmobiliaria(Inmueble*); //ESTA BIEN USAR * ?? O DEBO USAR & ??

};

#endif