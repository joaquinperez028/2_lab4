// WRAPPER DE LA COLECCION DE AGENDAS DE VISITA

#ifndef COLAGENDAVISITA_H
#define COLAGENDAVISITA_H

#include "ICollection.h"
#include "AgendaVisita.h"

class ColAgendaVisita {
private:
    ICollection* col;

public:
    ColAgendaVisita();
    void add(AgendaVisita* i);
    void remove(AgendaVisita* i);
    bool member(AgendaVisita* i);
    bool isEmpty();
    AgendaVisitaIterator* getIterator();
};

#endif
