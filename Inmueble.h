#ifndef INMUEBLE_H
#define INMUEBLE_H

#include <string>
#include "Datatypes/Direccion.h"
#include "Datatypes/Fecha.h"
#include "Datatypes/TipoInmueble.h"
#include "Datatypes/DTInmueble.h"
#include "Datatypes/DTEspecifica.h"
#include "Datatypes/DTInfoInmueble.h"
#include "ICollection.h"

using namespace std;

class Propietario;
class Administra;

class Inmueble : public ICollectible
{
protected:
    direccion direccion_;
    float superficie;
    fecha anoConstruc;
    int identificador;
    tipoInmueble tipo;

    Propietario *propietario;
    Administra *administra;

public:
    Inmueble(direccion dir, float superficie, fecha anoConstruc, int identificador, tipoInmueble tipoInm);
    virtual ~Inmueble();

    direccion getDireccion() const;
    float getSuperficie() const;
    fecha getAnoConstruc() const;
    int getIdentificador() const;
    tipoInmueble getTipo() const;
    Propietario *getPropietario() const;

    void asociarPropietario(Propietario *p);
    DTInfoInmueble *getDTInfoInmueble();
    DTInmueble *getDetalles();

    virtual void mostrarDetalle(int id) = 0;
    virtual DTEspecifica *getInmueble() = 0;

    void asociarAdministra(Administra *adm);
    ICollection *prepararEliminacion();
};

#endif
