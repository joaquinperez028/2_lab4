
#include "Publicacion.h"
#include "Administra.h"
#include "Inmueble.h"
#include "Datatypes/TipoInmueble.h"
#include "AgendaVisita.h"
#include "ICollection/collections/List.h"
#include "ICollection/interfaces/IIterator.h"
#include "Datatypes/DTPublicacion.h"

using namespace std;

Publicacion ::Publicacion(int codigo, string texto, float precio, Fecha fecha, TipoPublicacion tipo,
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

Fecha Publicacion ::getFecha()
{
    return this->fechaPublicacion;
}

bool Publicacion ::esActiva()
{
    return this->activa;
}

bool Publicacion ::precioFranja(float min, float max)
{
    return (this->precio <= max && this->precio >= min);
}

bool Publicacion ::coincideTipo(TipoPublicacion tipo)
{
    return this->tipo == tipo;
}

bool Publicacion ::compararInteres(Opciones interes)
{
    if (interes == Opciones::Todos)
        return true;

    if (interes == Opciones::InteresApto && this->administra->getInmueble()->getTipo() == TipoInmueble::Apartamento)
        return true;

    if (interes == Opciones::InteresCasa && this->administra->getInmueble()->getTipo() == TipoInmueble::Casa)
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
    if (this->agendas != nullptr)
    {
        eliminarAgendas();
    }
}

DTEspecifica *Publicacion::getDTEspecifica()
{
    return this->administra->getAdministra();
}

void Publicacion::agregarAgenda(AgendaVisita *agenda)
{
    if (agenda != nullptr)
    {
        this->agendas->add(agenda);
    }
}

void Publicacion::eliminarAgendas()
{
    if (this->agendas == nullptr)
        return;

    IIterator *it = this->agendas->getIterator();

    while (it->hasCurrent())
    {
        AgendaVisita *agenda = dynamic_cast<AgendaVisita *>(it->getCurrent());

        if (agenda != nullptr)
        {
            delete agenda;
        }

        it->next();
    }

    delete it;
    delete this->agendas;
    this->agendas = nullptr;
}

string Publicacion::getNickInmo()
{
    return this->administra->getInmo();
}

DTPublicacion *Publicacion::getPublicacion()
{
    string nickInmo = this->getNickInmo();
    return new DTPublicacion(
        this->activa,
        this->codigo,
        this->fechaPublicacion,
        this->texto,
        this->precio,
        nickInmo,
        this->tipo,
        this->administra->getInmueble()->getTipo());
}
