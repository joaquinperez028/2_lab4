//ESTO ES EL WRAPPER DE LA COLECCION DE ADMINISTRA
#ifndef COLADMINISTRA_H
#define COLADMINISTRA_H

#include "ICollection.h"
#include "Administra.h"

class ColAdministra {
    private:
        ICollection* col;
    public:
        ColAdministra();
        void add(Administra* i);
        void remove(Administra* i);
        bool member(Administra* i);
        bool isEmpty();
        
        AdministraIterator* getIterator(); 
    
};

#endif