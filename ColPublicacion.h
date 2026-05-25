//ESTO ES EL WRAPPER DE LA COLECCION DE PUBLICACIONES
#ifndef COLPUBLICACION_H
#define COLPUBLICACION_H

#include "ICollection.h"
#include "Publicacion.h"

class ColPublicacion {
    private:
        ICollection* col;
    public:
        ColPublicacion();
        void add(Publicacion* i);
        void remove(Publicacion* i);
        bool member(Publicacion* i);
        bool isEmpty();
        
        PublicacionIterator* getIterator(); 
    
};

#endif