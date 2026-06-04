#ifndef APARTAMENTO_H
#define APARTAMENTO_H

#include "Inmueble.h"
#include "Datatypes/DTEspecifica.h"
#include "Datatypes/DTApartamento.h"

class Propietario;

class Apartamento : public Inmueble {
private:
    int numPiso;
    bool ascensor;
    float gastosComunes;

public:
    Apartamento(direccion dir, float superficie, fecha anoConstruc, int identificador,
                int numPiso, bool ascensor, float gastosComunes, Propietario* propietario);

    int getNumPiso() const;
    bool getAscensor() const;
    float getGastosComunes() const;

    void mostrarDetalle(int id) override;
    DTEspecifica* getInmueble() override;
};

#endif
