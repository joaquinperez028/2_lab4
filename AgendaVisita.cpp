#include "AgendaVisita.h"

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
