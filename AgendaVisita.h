#ifndef AGENDAVISITA_H
#define AGENDAVISITA_H

#include "datatypes/datatypes.h"
#include <string>
using namespace std;

class Cliente;
class Publicacion;

class AgendaVisita {
    private:
        fecha fecha;
        string formaContacto;
        Cliente* cliente;
        Publicacion* publicacion;

    public:
        AgendaVisita(::fecha fecha, string formaContacto, Cliente* cliente, Publicacion* publicacion);
        ~AgendaVisita();

        ::fecha getFecha();
        string getFormaContacto();
        Cliente* getCliente();
        Publicacion* getPublicacion();
};

#endif
