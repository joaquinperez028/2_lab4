#ifndef CASA_H
#define CASA_H

#include "Inmueble.h"
#include "Datatypes/DTEspecifica.h"
#include "Datatypes/DTCasa.h"
#include "Datatypes/TipoTecho.h"

class Propietario;

class Casa : public Inmueble {
private:
    tipoTecho techo;
    bool propHorizontal;

public:
    Casa(direccion dir, float superficie, fecha anoConstruc, int identificador,
         tipoTecho techo, bool propHorizontal, Propietario* propietario);

    bool getPropHorizontal() const;
    tipoTecho getTipoTecho() const;

    void mostrarDetalle(int id) override;
    DTEspecifica* getInmueble() override;
};

#endif 