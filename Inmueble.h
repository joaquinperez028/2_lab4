#ifndef INMUEBLE_H
#define INMUEBLE_H

#include <string>
#include "Datatypes/Direccion.h"
#include "Datatypes/Fecha.h"
#include "Datatypes/TipoInmueble.h"
#include "Datatypes/DTInmueble.h"
#include "Datatypes/DTEspecifica.h"
#include "Datatypes/DTInfoInmueble.h"
#include "Datatypes/Opciones.h"
#include "ICollection.h"

using namespace std;

class Propietario;
class Administra;

class Inmueble : public ICollectible
{
protected:
    Direccion dir;
    float superficie;
    Fecha anoConstruc;
    int identificador;
    TipoInmueble tipo;

    Propietario *propietario;
    Administra *administra;

public:
    Inmueble(Direccion dir, float superficie, Fecha anoConstruc, int identificador, TipoInmueble tipo);
    virtual ~Inmueble();

    Direccion getDireccion() const;
    float getSuperficie() const;
    Fecha getAnoConstruc() const;
    int getIdentificador() const;
    TipoInmueble getTipo() const;
    Propietario *getPropietario() const;

    void asociarPropietario(Propietario *p);
    DTInfoInmueble *getDTInfoInmueble();
    DTInmueble *getDetalles();

    virtual void mostrarDetalle(int id) = 0;
    virtual DTEspecifica *getInmueble() = 0;

    void asociarAdministra(Administra *adm);
    ICollection *prepararEliminacion();
    bool compararInteres(Opciones interes);
};

#endif
