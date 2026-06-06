#include "Inmobiliaria.h"
#include "Administra.h"
#include "Inmueble.h"
#include "ICollection/collections/OrderedDictionary.h"
#include "ICollection/String.h"
#include "Propietario.h"
#include "ICollection/Integer.h"
#include "ICollection/collections/List.h"

Inmobiliaria::Inmobiliaria(string nickname, string nombre, string contrasenia, string email,
                           Direccion direccion, string telefono, string URL)
    : Usuario(nickname, nombre, contrasenia, email),
      email(email),
      dir(direccion),
      telefono(telefono),
      URL(URL),
      inmuebles(nullptr),
      administraciones(new OrderedDictionary()),
      propietarios(new OrderedDictionary())
{
}

Inmobiliaria::~Inmobiliaria()
{
    delete propietarios;
    delete inmuebles;
    delete administraciones;
}

string Inmobiliaria::getEmail()
{
    return this->email;
}

Direccion Inmobiliaria::getDireccion()
{
    return this->dir;
}

string Inmobiliaria::getTelefono()
{
    return this->telefono;
}

string Inmobiliaria::getUrl()
{
    return this->URL;
}

void Inmobiliaria::asociarPropietario(Propietario *propietario)
{
    if (this->propietarios == nullptr || propietario == nullptr)
    {
        return;
    }
    this->propietarios->add(new String(propietario->getNickName().c_str()), propietario);
}

Status Inmobiliaria::crearAdministra(Inmueble *inmu, Fecha fechaHoy)
{
    Administra *nueva = new Administra(this, inmu, fechaHoy);

    int ident = inmu->getIdentificador();
    Integer *key = new Integer(ident);

    if (administraciones->member(key))
    {
        delete key;
        return Status ::ERROR;
    }

    this->administraciones->add(key, nueva);
    inmu->asociarAdministra(nueva);

    return Status ::OK;
}

void Inmobiliaria::removerInmobiliaria(Inmueble *inmueble)
{
    if (inmueble == nullptr || this->administraciones == nullptr)
        return;

    Integer *key = new Integer(inmueble->getIdentificador());

    this->administraciones->remove(key);

    delete key;
}

Administra *Inmobiliaria ::findAdministra(int identificador)
{

    Integer *key = new Integer(identificador);

    ICollectible *val = administraciones->find(key);

    delete key;

    return dynamic_cast<Administra *>(val);
}

ICollection *Inmobiliaria ::getAdministras()
{

    ICollection *resultado = new List();

    IIterator *it = administraciones->getIterator();

    while (it->hasCurrent())
    {
        Administra *adm = (Administra *)it->getCurrent();
        DTAdministrados *nuevo = adm->getDTAdministrados();
        resultado->add(nuevo);

        it->next();
    }

    return resultado;
}

ICollection *Inmobiliaria::getInmueblesRepresentados()
{
    return new List();
}