#include "Inmobiliaria.h"
#include "ColUsuario.h"
#include "Propietario.h"

Inmobiliaria::Inmobiliaria(string nickname, string nombre, string contrasenia, string email,
                           direccion direccion, string telefono, string URL)
    : Usuario(nickname, nombre, contrasenia, email),
      direccion_(direccion),
      telefono(telefono),
      URL(URL),
      inmuebles(nullptr),
      administraciones(nullptr),
      propietarios(new ColUsuario())
{
}

Inmobiliaria::~Inmobiliaria()
{
    delete propietarios;
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

void Inmobiliaria::asociarPropietario(Propietario* propietario)
{
    if (this->propietarios == nullptr || propietario == nullptr)
    {
        return;
    }
    this->propietarios->add(propietario);
}

Status Inmobiliaria::crearAdministra(int)
{
    return Status::OK;
}

void Inmobiliaria::removerInmobiliaria(Inmueble*)
{
}
