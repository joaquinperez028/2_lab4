#ifndef INMOBILIARIA_H
#define INMOBILIARIA_H

#include "Usuario.h"
#include "Datatypes/Direccion.h"
#include "Datatypes/Status.h"

using namespace std;

class Propietario;
class Inmueble;
class ColInmueble;
class ColAdministra;
class ColUsuario;

class Inmobiliaria : public Usuario {
protected:
    direccion direccion_;
    string telefono;
    string URL;
    ColInmueble* inmuebles;
    ColAdministra* administraciones;
    ColUsuario* propietarios; // propietarios con los que trabaja (son Usuario)

public:
    Inmobiliaria(string nickname, string nombre, string contrasenia, string email,
                 direccion direccion, string telefono, string URL);
    ~Inmobiliaria();
    direccion getDireccion();
    string getTelefono();
    string getUrl();
    void asociarPropietario(Propietario* propietario);
    Status crearAdministra(int);
    void removerInmobiliaria(Inmueble*);
};

#endif
