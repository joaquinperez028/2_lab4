#include "AgendaVisita.h"

AgendaVisita::AgendaVisita(::fecha fecha, string formaContacto, Cliente *cliente, Publicacion *publicacion)
    : fecha(fecha), formaContacto(formaContacto), cliente(cliente), publicacion(publicacion)
{
}

AgendaVisita::~AgendaVisita() {}

::fecha AgendaVisita::getFecha()
{
    return fecha;
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
