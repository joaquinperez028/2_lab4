#include "AgendaVisita.h"
#include "Cliente.h"
#include "Publicacion.h"
#include "Datatypes/DTAgendaVisita.h"

AgendaVisita::AgendaVisita(::Fecha fecha, string formaContacto, Cliente *cliente, Publicacion *publicacion)
    : fechaVisita(fecha), formaContacto(formaContacto), cliente(cliente), publicacion(publicacion)
{
}

AgendaVisita::~AgendaVisita() {}

::Fecha AgendaVisita::getFecha()
{
    return fechaVisita;
}

string AgendaVisita::getFormaContacto()
{
    return formaContacto;
}

Cliente *AgendaVisita::getCliente()
{
    return cliente;
}

Publicacion *AgendaVisita::getPublicacion()
{
    return publicacion;
}

DTAgendaVisita *AgendaVisita::getDTAgendaVisita()
{
    string nick = "";
    string nombre = "";

    if (cliente != nullptr)
    {
        nick = cliente->getNickName();
        nombre = cliente->getNombre();
    }

    return new DTAgendaVisita(fechaVisita, formaContacto, nick, nombre);
}
