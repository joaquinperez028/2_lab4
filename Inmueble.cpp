#include "Inmueble.h"
#include "Propietario.h"
#include "Administra.h"
#include "Inmobiliaria.h"
#include <string>

// Constructor
Inmueble::Inmueble(direccion dir, float superficie, fecha anoConstruc, int identificador, tipoInmueble tipoInm)
{
    this->direccion_ = dir;
    this->superficie = superficie;
    this->anoConstruc = anoConstruc;
    this->identificador = identificador;
    this->tipo = tipoInm;
    this->propietario = nullptr;
    this->administra = nullptr;
}

// Destructor virtual — necesario para polimorfismo con punteros
Inmueble::~Inmueble()
{
    this->propietario = nullptr;
}

// --- Getters ---

direccion Inmueble::getDireccion() const
{
    return this->direccion_;
}

float Inmueble::getSuperficie() const
{
    return this->superficie;
}

fecha Inmueble::getAnoConstruc() const
{
    return this->anoConstruc;
}

int Inmueble::getIdentificador() const
{
    return this->identificador;
}

tipoInmueble Inmueble::getTipo() const
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
    return new DTInmueble(this->identificador, this->direccion_, this->anoConstruc, this->tipo);
}

DTInfoInmueble *Inmueble ::getDTInfoInmueble()
{
    DTInfoInmueble *resultado = new DTInfoInmueble(
        this->getIdentificador(),
        this->getDireccion());
    return resultado;
}

void Inmueble::asociarAdministra(Administra* adm)
{
    this->administra = adm;
}

ICollection* Inmueble::prepararEliminacion()
{
    ICollection* publicaciones = nullptr;

    if (this->propietario != nullptr)
    {
        this->propietario->removerPropietario(this);
        this->propietario = nullptr;
    }

    if (this->administra != nullptr)
    {
        publicaciones = this->administra->getPublicaciones();

        Inmobiliaria* inmo = this->administra->getInmobiliaria();

        if (inmo != nullptr)
        {
            inmo->removerInmobiliaria(this);
        }

        delete this->administra;
        this->administra = nullptr;
    }

    return publicaciones;
}