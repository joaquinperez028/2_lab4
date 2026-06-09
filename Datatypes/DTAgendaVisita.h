#ifndef DTAGENDAVISITA_H
#define DTAGENDAVISITA_H

#include <iostream>
#include <string>
#include "Fecha.h"
#include "ICollection/interfaces/ICollectible.h"

using namespace std;

class DTAgendaVisita : public ICollectible
{
private:
    Fecha fechaVisita;
    string formaContacto;
    string nicknameCliente;
    string nombreCliente;

public:
    DTAgendaVisita();
    DTAgendaVisita(Fecha fechaVisita, string formaContacto, string nicknameCliente, string nombreCliente);

    Fecha getFechaVisita();
    string getFormaContacto();
    string getNicknameCliente();
    string getNombreCliente();

    friend ostream &operator<<(ostream &os, const DTAgendaVisita &dt);
};

#endif
