#ifndef ADMINISTRA_H
#define ADMINISTRA_H

#include "ICollection/interfaces/ICollectible.h"
#include "datatypes/fecha.h"
#include "datatypes/DTEspecifica.h"
 

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
    
    fecha fecha;
    
    public:
    Administra(Inmobiliaria *inmo, Inmueble *inm);
    Inmobiliaria *getInmobiliaria();
    Inmueble *getInmueble();
    
    void agregarPublicacion(Publicacion *pub);
    
    virtual ~Administra();
    DTEspecifica* getAdministra();  // mensaje 2.1 del diagrama
};

#endif