#include "Propietario.h"
#include "Inmobiliaria.h"
#include "Casa.h"
#include "Apartamento.h"
#include "ICollection/collections/OrderedDictionary.h"
#include "ICollection/Integer.h"
#include "Datatypes/DTpropietario.h"
#include <iostream>
using namespace std;

Propietario::Propietario(string nickname, string nombre, string contrasenia, string email,
                         string numCuenta, string banco, string telefono)
    : Usuario(nickname, nombre, contrasenia, email),
      numCuenta(numCuenta),
      banco(banco),
      telefono(telefono),
      inmuebles(new OrderedDictionary()),
      inmo(nullptr)
{
}

Propietario::~Propietario()
{
    // ojo cuando se implemente el destructor, como elimina o desasocia la coleccion de inmuebles...
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

void Propietario::asociarInmobiliaria(Inmobiliaria *inmobiliaria)
{
    this->inmo = inmobiliaria;
}

void Propietario::removerPropietario(Inmueble *inmueble)
{
    if (inmueble == nullptr)
        return;

    Integer *key = new Integer(inmueble->getIdentificador());

    this->inmuebles->remove(key);

    delete key;
}

Casa *Propietario::crearCasa(Direccion direccion_, float superficie, Fecha anoConstruc,
                             int identificador, TipoTecho tipoTecho, bool propHorizontal)
{
    Casa *casa = new Casa(direccion_, superficie, anoConstruc, identificador,
                          tipoTecho, propHorizontal, this);

    this->inmuebles->add(new Integer(identificador), casa);

    return casa; // cambiar en diagrama que esta operacion retorne el objeto casa
}

Apartamento *Propietario::crearApto(Direccion direccion_, float superficie, Fecha anoConstruc,
                                    int identificador, int numPiso, bool ascensor,
                                    float gastosComunes)
{
    Apartamento *apartamento = new Apartamento(direccion_, superficie, anoConstruc,
                                               identificador, numPiso, ascensor,
                                               gastosComunes, this);

    this->inmuebles->add(new Integer(identificador), apartamento);

    return apartamento; // cambiar en diagrama que esta operacion retorne el objeto apto
}

DTPropietario *Propietario::getDTPropietario()
{
    return new DTPropietario(this->getNickName(), this->getNombre());
}