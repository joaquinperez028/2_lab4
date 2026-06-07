#ifndef ADMINISTRA_H
#define ADMINISTRA_H

#include "ICollection/interfaces/ICollectible.h"
#include "Datatypes/Fecha.h"
#include "Datatypes/TipoPublicacion.h"
#include "Publicacion.h"
#include "Datatypes/DTEspecifica.h"
#include "Datatypes/DTAdministrados.h"
#include "Datatypes/Opciones.h"

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
    Fecha fechaInicio;

public:
    Administra(Inmobiliaria *inmo, Inmueble *inm, Fecha fechaIni);
    Inmobiliaria *getInmobiliaria();
    Inmueble *getInmueble();

    void agregarPublicacion(Publicacion *pub);
    void limpiarPublicaciones();
    bool existePubAciva(TipoPublicacion tipo, Fecha fechaHoy);
    Publicacion *crearPublicacion(int codigo, TipoPublicacion tipo, std::string texto, float precio,
                                  Fecha fechaHoy);
    DTAdministrados *getDTAdministrados();
    virtual ~Administra();
    DTEspecifica *getAdministra();
    ICollection* getPublicaciones();
    string getInmo();
    bool compararInteres(Opciones interes);
};

#endif
