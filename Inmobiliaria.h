#ifndef INMOBILIARIA_H
#define INMOBILIARIA_H

#include "Usuario.h"
#include "ICollection.h"
#include "ICollection/interfaces/IDictionary.h"
#include "Datatypes/Direccion.h"
#include "Datatypes/Status.h"

using namespace std;

class Propietario;
class Inmueble;
class Administra;

class Inmobiliaria : public Usuario
{
protected:
    direccion direccion_;
    string telefono;
    string URL;
    IDictionary *inmuebles;
    IDictionary *administraciones;
    IDictionary *propietarios;

public:
    Inmobiliaria(string nickname, string nombre, string contrasenia, string email,
                 direccion direccion, string telefono, string URL);
    ~Inmobiliaria();
    direccion getDireccion();
    string getTelefono();
    string getUrl();
    void asociarPropietario(Propietario *propietario);
    Status crearAdministra(int);
    void removerInmobiliaria(Inmueble *);
    Administra *findAdministra(int identificador);
    ICollection *getAdministras();
    ICollection *getInmueblesRepresentados();
};

#endif
