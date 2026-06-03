#include "Inmueble.h"
#include "Propietario.h"
#include <string>

// Constructor
Inmueble::Inmueble(direccion dir, float superficie, fecha anoConstruc, int identificador, tipoInmueble tipo)
{
    this->direccion_ = dir;
    this->superficie = superficie;
    this->anoConstruc = anoConstruc;
    this->identificador = identificador;
    this->tipo = tipo;
    this->propietario = nullptr;
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

// Remueve el link entre este inmueble y su propietario
// inm es el THIS que viene del diagrama de comunicacion
void Inmueble::removerInmueble(Inmueble *inm)
{
    if (this->propietario != nullptr)
    {
        this->propietario->removerPropietario(inm);
    }
    this->propietario = nullptr;
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