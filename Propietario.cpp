#include "Propietario.h"
#include "Inmobiliaria.h"

Propietario::Propietario(string nickname, string nombre, string contrasenia, string email,
                         string numCuenta, string banco, string telefono)
    : Usuario(nickname, nombre, contrasenia, email),
      numCuenta(numCuenta),
      banco(banco),
      telefono(telefono),
      inmuebles(nullptr),
      inmo(nullptr)
{
}

Propietario::~Propietario()
{
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

Status Propietario::altaCasa(direccion, float, int, tipoTecho, bool)
{
    return Status::OK;
}

Status Propietario::altaApto(direccion, float, int, int, bool, float)
{
    return Status::OK;
}
