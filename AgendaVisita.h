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
    fecha fecha;
    string formaContacto;
    Cliente *cliente;
    Publicacion *publicacion;

public:
    AgendaVisita(::fecha fecha, string formaContacto, Cliente *cliente, Publicacion *publicacion);
    ~AgendaVisita();

    ::fecha getFecha();
    string getFormaContacto();
    Cliente *getCliente();
    Publicacion *getPublicacion();
};

#endif
