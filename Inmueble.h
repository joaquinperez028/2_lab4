#ifndef INMUEBLE_H
#define INMUEBLE_H

#include <string>
#include "Datatypes/Direccion.h"
#include "Datatypes/Fecha.h"
#include "Datatypes/TipoInmueble.h"
#include "Datatypes/DTprop.h"
#include "Datatypes/DTEspecifica.h"
#include "datatypes/DTInfoInmueble.h"
#include "ICollection.h"

using namespace std;

class Propietario;

class Inmueble : public ICollectible
{
protected:
    direccion direccion_;
    float superficie;
    fecha anoConstruc;
    int identificador;
    tipoInmueble tipo;

    Propietario *propietario;

public:
    Inmueble(direccion dir, float superficie, fecha anoConstruc, int identificador, tipoInmueble tipo);
    virtual ~Inmueble();

    // Getters
    direccion getDireccion() const;
    float getSuperficie() const;
    fecha getAnoConstruc() const;
    int getIdentificador() const;
    tipoInmueble getTipo() const;
    Propietario *getPropietario() const;

    // Operaciones
    void asociarPropietario(Propietario *p);
    void removerInmueble(Inmueble *inm);
    DTInfoInmueble *getDTInfoInmueble();

    // Para listarPropiedades — mensaje 2* en el diagrama
    DTprop *getDetalles();

    virtual void mostrarDetalle(int id) = 0;
    virtual DTEspecifica *getInmueble() = 0; // mensaje 2.1.1 del diagrama
};

#endif