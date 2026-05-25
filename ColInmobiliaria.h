// WRAPPER DE LA COLECCION INMOBILIARIA
#ifndef COLINMOBILIARIA_H
#define COLINMOBILIARIA_H

#include "ICollection.h"
#include "Inmobiliaria.h"

class ColInmobiliaria {
    private:
        ICollection* col;
    public:
        ColInmobiliaria();
        void add(Inmobiliaria* i);
        void remove(Inmobiliaria* i);
        bool member(Inmobiliaria* i);
        bool isEmpty();
        
        InmobiliariaIterator* getIterator(); 
    
};

#endif