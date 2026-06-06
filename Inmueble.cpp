#include "Inmueble.h"
#include "Propietario.h"
#include "Administra.h"
#include "Inmobiliaria.h"
#include <string>

// Constructor
Inmueble::Inmueble(Direccion dir, float superficie, Fecha anoConstruc, int identificador, TipoInmueble tipo)
{
    this->dir = dir;
    this->superficie = superficie;
    this->anoConstruc = anoConstruc;
    this->identificador = identificador;
    this->tipo = tipo;
    this->propietario = nullptr;
    this->administra = nullptr;
}

// Destructor virtual — necesario para polimorfismo con punteros
Inmueble::~Inmueble()
{
    this->propietario = nullptr;
}

// --- Getters ---

Direccion Inmueble::getDireccion() const
{
    return this->dir;
}

float Inmueble::getSuperficie() const
{
    return this->superficie;
}

Fecha Inmueble::getAnoConstruc() const
{
    return this->anoConstruc;
}

int Inmueble::getIdentificador() const
{
    return this->identificador;
}

TipoInmueble Inmueble::getTipo() const
{
    return this->tipo;
}

Propietario *Inmueble::getPropietario() const
{
    return this->propietario;
}

// --- Operaciones ---

// Asocia un propietario a este inmueble
void Inmueble::asociarPropietario(Propietario *p)
{
    this->propietario = p;
}

// Corresponde al mensaje 2* getDetalles() del diagrama de listarPropiedades
DTInmueble *Inmueble::getDetalles()
{
    return new DTInmueble(this->identificador, this->dir, this->anoConstruc, this->tipo);
}

DTInfoInmueble *Inmueble ::getDTInfoInmueble()
{
    DTInfoInmueble *resultado = new DTInfoInmueble(
        this->getIdentificador(),
        this->getDireccion());
    return resultado;
}

void Inmueble::asociarAdministra(Administra *adm)
{
    this->administra = adm;
}

ICollection *Inmueble::prepararEliminacion()
{
    ICollection *publicaciones = nullptr;

    if (this->propietario != nullptr)
    {
        this->propietario->removerPropietario(this);
        this->propietario = nullptr;
    }

    if (this->administra != nullptr)
    {
        publicaciones = this->administra->getPublicaciones();

        Inmobiliaria *inmo = this->administra->getInmobiliaria();

        if (inmo != nullptr)
        {
            inmo->removerInmobiliaria(this);
        }

        delete this->administra;
        this->administra = nullptr;
    }

    return publicaciones;
}