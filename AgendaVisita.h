#ifndef AGENDAVISITA_H
#define AGENDAVISITA_H

#include "Datatypes/Fecha.h"
#include <string>

using namespace std;

class Cliente;
class Publicacion;

class AgendaVisita : public ICollectible
{
private:
    Fecha fechaVisita;
    string formaContacto;
    Cliente *cliente;
    Publicacion *publicacion;

public:
    AgendaVisita(::Fecha fecha, string formaContacto, Cliente *cliente, Publicacion *publicacion);
    ~AgendaVisita();

    ::Fecha getFecha();
    string getFormaContacto();
    Cliente *getCliente();
    Publicacion *getPublicacion();
};

#endif
