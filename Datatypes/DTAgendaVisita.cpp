#include "DTAgendaVisita.h"

DTAgendaVisita::DTAgendaVisita() {}

DTAgendaVisita::DTAgendaVisita(Fecha fechaVisita, string formaContacto, string nicknameCliente, string nombreCliente)
    : fechaVisita(fechaVisita), formaContacto(formaContacto), nicknameCliente(nicknameCliente), nombreCliente(nombreCliente)
{
}

Fecha DTAgendaVisita::getFechaVisita()
{
    return fechaVisita;
}

string DTAgendaVisita::getFormaContacto()
{
    return formaContacto;
}

string DTAgendaVisita::getNicknameCliente()
{
    return nicknameCliente;
}

string DTAgendaVisita::getNombreCliente()
{
    return nombreCliente;
}

ostream &operator<<(ostream &os, const DTAgendaVisita &dt)
{
    os << "Fecha: " << dt.fechaVisita
       << " | Contacto: " << dt.formaContacto
       << " | Cliente: " << dt.nicknameCliente
       << " (" << dt.nombreCliente << ")";
    return os;
}
