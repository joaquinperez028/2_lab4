
#include "Publicacion.h"
#include "Administra.h"
#include "Inmueble.h"
#include "Datatypes/TipoInmueble.h"
#include "AgendaVisita.h"
#include "ICollection/collections/List.h"
#include "ICollection/interfaces/IIterator.h"

using namespace std;

Publicacion ::Publicacion(int codigo, string texto, float precio, fecha fecha, tipoPublicacion tipo,
                          Administra *adm)
{
    this->codigo = codigo;
    this->texto = texto;
    this->precio = precio;
    this->fechaPublicacion = fecha;
    this->tipo = tipo;
    this->administra = adm;
    this->activa = true;
    this->agendas = new List();
}

int Publicacion ::getCodigo()
{
    return this->codigo;
}

string Publicacion ::getTexto()
{
    return this->texto;
}

float Publicacion ::getPrecio()
{
    return this->precio;
}

fecha Publicacion ::getFecha()
{
    return this->fechaPublicacion;
}

bool Publicacion ::esActiva()
{
    if (this->activa == true)
        return true;
    return false;
}

bool Publicacion ::precioFranja(float min, float max)
{
    return (this->precio <= max && this->precio >= min);
}

bool Publicacion ::coincideTipo(tipoPublicacion tipo)
{
    if (this->tipo == tipo)
        return true;
    return false;
}

bool Publicacion ::compararInteres(opciones interes)
{
    if (interes == opciones::Todos)
        return true;

    if (interes == opciones::InteresApto && this->administra->getInmueble()->getTipo() == tipoInmueble::Apartamento)
        return true;

    if (interes == opciones::InteresCasa && this->administra->getInmueble()->getTipo() == tipoInmueble::Casa)
        return true;

    return false;
}

void Publicacion ::desactivar()
{
    this->activa = false;
}

Administra *Publicacion ::getAdministra()
{
    return this->administra;
}

Publicacion ::~Publicacion()
{
    if(this->agendas != nullptr)
    {
        eliminarAgendas();
    }
}

// Corresponde al mensaje 2: getDTEspecifica():DTEspecifica
// Publicacion delega a Administra — mensaje 2.1
DTEspecifica* Publicacion::getDTEspecifica() {
    return this->administra->getAdministra();
}