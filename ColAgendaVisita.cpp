// IMPLEMENTACION DEL WRAPPER DE LA COLECCION DE AGENDAS DE VISITA

#include "ColAgendaVisita.h"
#include // ACA HAY QUE INCLUIR EL TIPO DE ESTRUCTURA QUE VAMOS A USAR, LISTA O ARBOL, ETC .H

ColAgendaVisita::ColAgendaVisita() {
    this->col = new //DE LISTA O ARBOL O ETC, LO QUE HAYAMOS ELEGIDO();
}

void ColAgendaVisita::add(AgendaVisita* i) {
    this->col->add(i);
}

void ColAgendaVisita::remove(AgendaVisita* i) {
}

bool ColAgendaVisita::member(AgendaVisita* i) {
}

bool ColAgendaVisita::isEmpty() {
}

AgendaVisitaIterator* ColAgendaVisita::getIterator() { // CASTEO DEL OBJETO
    return new AgendaVisitaIterator(this->col->getIterator()); // ITERADOR GENERICO QUE DEVUELVE AL OBJETO CONCRETO
}
