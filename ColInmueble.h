//ESTO ES EL WRAPPER DE LA COLECCION DE INMUEBLES
#ifndef COLINMUEBLE_H
#define COLINMUEBLE_H

#include "ICollection.h"
#include "InmuebleIterator.h"
#include "Inmueble.h"

class ColInmueble {
    private:
        ICollection* col;
    public:
        ColInmueble();
        void add(Inmueble* i);
        void remove(Inmueble* i);
        bool member(Inmueble* i);
        bool isEmpty();
        
        InmuebleIterator* getIterator(); 
    
};

#endif