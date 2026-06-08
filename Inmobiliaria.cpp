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
    limpiarPropietarios();
    limpiarAdministraciones();
    delete propietarios;
    delete inmuebles;
    delete administraciones;
    propietarios = nullptr;
    inmuebles = nullptr;
    administraciones = nullptr;
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

void Inmobiliaria::desasociarPropietario(Propietario *propietario)
{
    if (this->propietarios == nullptr || propietario == nullptr)
        return;

    String *key = new String(propietario->getNickName().c_str());
    this->propietarios->remove(key);
    delete key;
}

void Inmobiliaria::limpiarPropietarios()
{
    if (this->propietarios == nullptr)
        return;

    delete this->propietarios;
    this->propietarios = new OrderedDictionary();
}

void Inmobiliaria::limpiarAdministraciones()
{
    if (this->administraciones == nullptr)
        return;

    ICollection *pendientes = new List();
    IIterator *it = this->administraciones->getIterator();

    while (it->hasCurrent())
    {
        pendientes->add(it->getCurrent());
        it->next();
    }
    delete it;

    IIterator *itA = pendientes->getIterator();
    while (itA->hasCurrent())
    {
        Administra *adm = dynamic_cast<Administra *>(itA->getCurrent());
        itA->next();

        if (adm != nullptr)
        {
            Inmueble *inm = adm->getInmueble();
            if (inm != nullptr)
            {
                Integer *key = new Integer(inm->getIdentificador());
                this->administraciones->remove(key);
                delete key;
            }
            delete adm;
        }
    }
    delete itA;
    delete pendientes;
}

Status Inmobiliaria::crearAdministra(Inmueble *inmu, Fecha fechaHoy)
{
    int ident = inmu->getIdentificador();
    Integer *key = new Integer(ident);

    if (administraciones->member(key))
    {
        Administra *existente = dynamic_cast<Administra *>(administraciones->find(key));
        if (existente != nullptr)
        {
            Inmueble *inmExist = existente->getInmueble();
            if (inmExist == inmu && inmu->getAdministra() == existente)
            {
                delete key;
                return Status::ERROR;
            }
        }
        eliminarAdministracion(ident, inmu);
    }
    delete key;

    Administra *nueva = new Administra(this, inmu, fechaHoy);
    key = new Integer(ident);
    this->administraciones->add(key, nueva);
    inmu->asociarAdministra(nueva);

    return Status::OK;
}

void Inmobiliaria::eliminarAdministracion(int identificador, Inmueble *inmueble)
{
    if (this->administraciones == nullptr)
        return;

    Integer *key = new Integer(identificador);
    Administra *adm = dynamic_cast<Administra *>(this->administraciones->find(key));

    if (adm == nullptr)
    {
        delete key;
        return;
    }

    Inmueble *inmAdm = adm->getInmueble();
    if (inmAdm != nullptr && inmAdm->getAdministra() == adm)
        inmAdm->desasociarAdministra();
    else if (inmueble != nullptr && inmueble->getAdministra() == adm)
        inmueble->desasociarAdministra();

    this->administraciones->remove(key);
    delete key;
    delete adm;
}

void Inmobiliaria::removerInmobiliaria(Inmueble *inmueble)
{
    if (inmueble == nullptr)
        return;

    eliminarAdministracion(inmueble->getIdentificador(), inmueble);
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
    ICollection *resultado = new List();

    if (this->propietarios == nullptr)
        return resultado;

    IIterator *it = this->propietarios->getIterator();
    while (it->hasCurrent())
    {
        Propietario *prop = dynamic_cast<Propietario *>(it->getCurrent());
        if (prop != nullptr)
        {
            ICollection *inmueblesProp = prop->listarInmueblesRepresentados();
            IIterator *itInm = inmueblesProp->getIterator();

            while (itInm->hasCurrent())
            {
                resultado->add(itInm->getCurrent());
                itInm->next();
            }
            delete itInm;
            delete inmueblesProp;
        }
        it->next();
    }
    delete it;

    return resultado;
}

ICollection *Inmobiliaria::getPropietariosRepresentados()
{
    ICollection *resultado = new List();

    if (this->propietarios == nullptr)
        return resultado;

    IIterator *it = this->propietarios->getIterator();
    while (it->hasCurrent())
    {
        Propietario *prop = dynamic_cast<Propietario *>(it->getCurrent());
        if (prop != nullptr)
            resultado->add(prop->getDTPropietario());
        it->next();
    }
    delete it;

    return resultado;
}