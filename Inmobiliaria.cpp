#include "Inmobiliaria.h"
#include "Administra.h"
#include "ICollection/collections/OrderedDictionary.h"
#include "ICollection/String.h"
#include "Propietario.h"
#include "ICollection/Integer.h"

Inmobiliaria::Inmobiliaria(string nickname, string nombre, string contrasenia, string email,
                           direccion direccion, string telefono, string URL)
    : Usuario(nickname, nombre, contrasenia, email),
      direccion_(direccion),
      telefono(telefono),
      URL(URL),
      inmuebles(nullptr),
      administraciones(nullptr),
      propietarios(new OrderedDictionary())
{
}

Inmobiliaria::~Inmobiliaria()
{
    delete propietarios;
    delete inmuebles;
    delete administraciones;
}

direccion Inmobiliaria::getDireccion()
{
    return this->direccion_;
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

Status Inmobiliaria::crearAdministra(int)
{
    return Status::OK;
}

void Inmobiliaria::removerInmobiliaria(Inmueble *)
{
}

Administra *Inmobiliaria ::findAdministra(int identificador)
{

    Integer *key = new Integer(identificador);

    ICollectible *val = administraciones->find(key);

    delete key;

    return dynamic_cast<Administra *>(val);
}