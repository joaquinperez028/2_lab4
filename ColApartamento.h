#ifndef COLAPARTAMENTO_H
#define COLAPARTAMENTO_H
 
#include "ICollection.h"
#include "Apartamento.h"
 
class ColApartamento {
    private:
        ICollection* col;
    public:
        ColApartamento();
        void add(Apartamento* i);
        void remove(Apartamento* i);
        bool member(Apartamento* i);
        bool isEmpty();
 
        ApartamentoIterator* getIterator();
};
 
#endif
 