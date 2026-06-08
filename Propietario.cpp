#include "Propietario.h"
#include "Inmobiliaria.h"
#include "Sistema.h"
#include "Inmueble.h"
#include "Casa.h"
#include "Apartamento.h"
#include "ICollection/collections/OrderedDictionary.h"
#include "ICollection/collections/List.h"
#include "ICollection/Integer.h"
#include "Datatypes/DTpropietario.h"
#include "ICollection/interfaces/IIterator.h"
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
    desasociarInmobiliaria();
    limpiarInmuebles(Sistema::getInstance());
    delete inmuebles;
    inmuebles = nullptr;
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

void Propietario::desasociarInmobiliaria()
{
    if (this->inmo == nullptr)
        return;

    this->inmo->desasociarPropietario(this);
    this->inmo = nullptr;
}

Inmobiliaria *Propietario::getInmobiliaria()
{
    return this->inmo;
}

void Propietario::limpiarInmuebles(Sistema *sistema)
{
    if (this->inmuebles == nullptr || this->inmuebles->isEmpty() || sistema == nullptr)
        return;

    ICollection *codigos = new List();
    IIterator *it = this->inmuebles->getIterator();

    while (it->hasCurrent())
    {
        Inmueble *inm = dynamic_cast<Inmueble *>(it->getCurrent());
        if (inm != nullptr)
            codigos->add(new Integer(inm->getIdentificador()));
        it->next();
    }
    delete it;

    IIterator *itCod = codigos->getIterator();
    while (itCod->hasCurrent())
    {
        Integer *cod = dynamic_cast<Integer *>(itCod->getCurrent());
        if (cod != nullptr)
            sistema->eliminarInmueble(cod->getValue());
        itCod->next();
    }
    delete itCod;

    IIterator *itClean = codigos->getIterator();
    while (itClean->hasCurrent())
    {
        delete itClean->getCurrent();
        itClean->next();
    }
    delete itClean;
    delete codigos;
}

ICollection *Propietario::listarInmueblesRepresentados()
{
    ICollection *lista = new List();

    if (this->inmuebles == nullptr)
        return lista;

    IIterator *it = this->inmuebles->getIterator();
    while (it->hasCurrent())
    {
        Inmueble *inm = dynamic_cast<Inmueble *>(it->getCurrent());
        if (inm != nullptr)
            lista->add(inm->getDTInmuebleRep());
        it->next();
    }
    delete it;

    return lista;
}

void Propietario::removerPropietario(Inmueble *inmueble)
{
    if (inmueble == nullptr || this->inmuebles == nullptr)
        return;

    Integer *key = new Integer(inmueble->getIdentificador());
    this->inmuebles->remove(key);
    delete key;

    IIterator *it = this->inmuebles->getIterator();
    while (it->hasCurrent())
    {
        Inmueble *inm = dynamic_cast<Inmueble *>(it->getCurrent());
        if (inm == inmueble)
        {
            Integer *k = new Integer(inm->getIdentificador());
            this->inmuebles->remove(k);
            delete k;
            break;
        }
        it->next();
    }
    delete it;
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