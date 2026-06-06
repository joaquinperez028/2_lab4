#ifndef CASA_H
#define CASA_H

#include "Inmueble.h"
#include "Datatypes/DTEspecifica.h"
#include "Datatypes/DTCasa.h"
#include "Datatypes/TipoTecho.h"

class Propietario;

class Casa : public Inmueble
{
private:
    TipoTecho techo;
    bool propHorizontal;

public:
    Casa(Direccion dir, float superficie, Fecha anoConstruc, int identificador,
         TipoTecho techo, bool propHorizontal, Propietario *propietario);

    bool getPropHorizontal() const;
    TipoTecho getTipoTecho() const;

    void mostrarDetalle(int id) override;
    DTEspecifica *getInmueble() override;
};

#endif