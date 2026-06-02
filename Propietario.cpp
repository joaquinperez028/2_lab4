#include "Propietario.h"
#include "Inmobiliaria.h"
#include "Casa.h"
#include "Apartamento.h"
#include "ICollection/collections/OrderedDictionary.h"
#include "ICollection/Integer.h"
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

Casa* Propietario::crearCasa(direccion direccion_, float superficie, fecha anoConstruc,
                              int identificador, tipoTecho tipoTecho, bool propHorizontal)
{   
    Casa* casa = new Casa(direccion_, superficie, anoConstruc, identificador,
                          tipoTecho, propHorizontal, this);

    this->inmuebles->add(new Integer(identificador), casa);

    return casa; //cambiar en diagrama que esta operacion retorne el objeto casa
}


Apartamento* Propietario::crearApto(direccion direccion_, float superficie, fecha anoConstruc,
                                     int identificador, int numPiso, bool ascensor,
                                     float gastosComunes)
{   
    Apartamento* apartamento = new Apartamento(direccion_, superficie, anoConstruc,
                                               identificador, numPiso, ascensor,
                                               gastosComunes, this);

    this->inmuebles->add(new Integer(identificador), apartamento);

    return apartamento; //cambiar en diagrama que esta operacion retorne el objeto apto
}
/*DTprop* Propietario::getDTprop()
{
    return new DTprop(this->getNombre(), this->getNickName());
}*/// esto hay que agregarlo (yani)
