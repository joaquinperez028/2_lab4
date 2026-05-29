#include "Propietario.h"
#include "Inmobiliaria.h"
#include "ColInmueble.h"

Propietario::Propietario(string nickname, string nombre, string contrasenia, string email,
                         string numCuenta, string banco, string telefono)
    : Usuario(nickname, nombre, contrasenia, email),
      numCuenta(numCuenta),
      banco(banco),
      telefono(telefono),
      inmuebles(new ColInmueble()),
      inmo(nullptr)
{
}

Propietario::~Propietario()
{
    //ojo cuando se implemente el destructor, como elimina o desasocia la coleccion de inmuebles...
}

string Propietario::getNumCuenta()
{
    return this->numCuenta;
}

string Propietario::getBanco()
{
    return this->banco;
}

string Propietario::getTelefono()
{
    return this->telefono;
}

void Propietario::asociarInmobiliaria(Inmobiliaria* inmobiliaria)
{
    this->inmo = inmobiliaria;
}

void Propietario::removerPropietario(Inmueble*)
{
}

Status Propietario::altaCasa(direccion direccion_, float superficie, int identificador,
                              TipoTecho tipoTecho, bool propHorizontal)
{
    Casa *casa = new Casa(direccion_, superficie, identificador, techo, propHorizontal);

    casa->asociarPropietario(this);
    this->inmuebles->add(casa);

    return Status::OK;
}

Status Propietario::altaApto(direccion, float, int, int, bool, float)
{
    return Status::OK;
}
