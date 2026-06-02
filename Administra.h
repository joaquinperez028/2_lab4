#ifndef ADMINISTRA_H
#define ADMINISTRA_H

#include "ICollection/interfaces/ICollectible.h"
#include "datatypes/fecha.h"
#include "datatypes/tipoPublicacion.h"
#include "Publicacion.h"

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

    fecha fechaInicio;

public:
    Administra(Inmobiliaria *inmo, Inmueble *inm);
    Inmobiliaria *getInmobiliaria();
    Inmueble *getInmueble();

    void agregarPublicacion(Publicacion *pub);
    bool existePubAciva(tipoPublicacion tipo, fecha fechaHoy);
    Publicacion *crearPublicacion(int codigo, tipoPublicacion tipo, std::string texto, float precio,
                                  fecha fechaHoy);

    virtual ~Administra();
};

#endif