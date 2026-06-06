#ifndef INMOBILIARIA_H
#define INMOBILIARIA_H

#include "Usuario.h"
#include "ICollection.h"
#include "ICollection/interfaces/IDictionary.h"
#include "Datatypes/Direccion.h"
#include "Datatypes/Status.h"
#include "Datatypes/Fecha.h"

using namespace std;

class Propietario;
class Inmueble;
class Administra;

class Inmobiliaria : public Usuario
{
protected:
    Direccion dir;
    string telefono;
    string URL;
    IDictionary *inmuebles;
    IDictionary *administraciones;
    IDictionary *propietarios;

public:
    Inmobiliaria(string nickname, string nombre, string contrasenia, string email,
                 Direccion direccion, string telefono, string URL);
    ~Inmobiliaria();
    Direccion getDireccion();
    string getTelefono();
    string getUrl();
    void asociarPropietario(Propietario *propietario);
    Status crearAdministra(Inmueble *inmu, Fecha fechaHoy);
    void removerInmobiliaria(Inmueble *);
    Administra *findAdministra(int identificador);
    ICollection *getAdministras();
    ICollection *getInmueblesRepresentados();
};

#endif
