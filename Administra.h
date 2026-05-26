#ifndef ADMINISTRA_H
#define ADMINISTRA_H

#include "ICollecitble.h"
#include "fecha.h"

class Inmobiliaria;
class Inmueble;
class Publicacion;
class ICollection;

class Administra : public ICollectible
{

private:
    Inmobiliaria *inmobiliaria;
    Inmueble *inmueble;
    ICollection *publicaciones;

    fecha : fecha;

public:
    Administra(Inmobiliaria *inmo, Inmueble *inm);
    Inmobiliaria *getInmobiliaria();
    Inmueble *getInmueble();

    void agregarPublicacion(Publicacion *pub);

    virtual ~Administra();
}

#endif