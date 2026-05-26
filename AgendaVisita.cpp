#include "AgendaVisita.h"

AgendaVisita::AgendaVisita(::fecha fecha, string formaContacto, Cliente* cliente, Publicacion* publicacion) {
    this->fecha = fecha;
    this->formaContacto = formaContacto;
    this->cliente = cliente;
    this->publicacion = publicacion;
}

AgendaVisita::~AgendaVisita() {}

fecha AgendaVisita::getFecha() {
    return fecha;
}

string AgendaVisita::getFormaContacto() {
    return formaContacto;
}

Cliente* AgendaVisita::getCliente() {
    return cliente;
}

Publicacion* AgendaVisita::getPublicacion() {
    return publicacion;
}
