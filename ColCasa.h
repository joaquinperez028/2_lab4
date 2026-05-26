#ifndef COLCASA_H
#define COLCASA_H
 
#include "ICollection.h"
#include "Casa.h"
 
class ColCasa {
    private:
        ICollection* col;
    public:
        ColCasa();
        void add(Casa* i);
        void remove(Casa* i);
        bool member(Casa* i);
        bool isEmpty();
 
        CasaIterator* getIterator();
};
 
#endif