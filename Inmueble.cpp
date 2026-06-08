#include "Inmueble.h"
#include "Propietario.h"
#include "Datatypes/DTPropiedad.h"
#include "Datatypes/DTInmuebleRep.h"
#include "Administra.h"
#include "Inmobiliaria.h"
#include "Datatypes/Opciones.h"
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
    desasociarPropietario();
    desasociarAdministra();
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

void Inmueble::desasociarPropietario()
{
    this->propietario = nullptr;
}

Administra *Inmueble::getAdministra() const
{
    return this->administra;
}

void Inmueble::desasociarAdministra()
{
    this->administra = nullptr;
}

// Corresponde al mensaje 2* getDetalles() del diagrama de listarPropiedades
DTInmueble *Inmueble::getDetalles()
{
    return new DTInmueble(this->identificador, this->dir, this->anoConstruc, this->tipo);
}

DTPropiedad *Inmueble::getDTPropiedad()
{
    string nombre = "";
    if (this->propietario != nullptr)
    {
        nombre = this->propietario->getNombre();
    }

    return new DTPropiedad(this->identificador, this->dir, this->anoConstruc, nombre);
}

DTInmuebleRep *Inmueble::getDTInmuebleRep()
{
    string nombre = "";
    if (this->propietario != nullptr)
        nombre = this->propietario->getNombre();

    return new DTInmuebleRep(this->identificador, this->dir, nombre);
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
    Inmobiliaria *inmo = nullptr;

    if (this->administra != nullptr)
    {
        inmo = this->administra->getInmobiliaria();
        publicaciones = this->administra->getPublicaciones();
    }
    else if (this->propietario != nullptr)
    {
        inmo = this->propietario->getInmobiliaria();
    }

    if (this->propietario != nullptr)
    {
        this->propietario->removerPropietario(this);
        this->propietario = nullptr;
    }

    if (inmo != nullptr)
    {
        inmo->eliminarAdministracion(this->identificador, this);
    }
    else if (this->administra != nullptr)
    {
        delete this->administra;
        this->administra = nullptr;
    }

    return publicaciones;
}

bool Inmueble::compararInteres(Opciones interes) {
    if (interes == Opciones::Todos)
        return true;
    if (interes == Opciones::InteresApto && this->tipo == TipoInmueble::Apartamento)
        return true;
    if (interes == Opciones::InteresCasa && this->tipo == TipoInmueble::Casa)
        return true;
    return false;
}