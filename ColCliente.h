// WRAPPER DE LA COLECCION DE CLIENTES

#ifndef COLCLIENTE_H
#define COLCLIENTE_H

#include "ICollection.h"
#include "Cliente.h"

class ColCliente {
private:
    ICollection* col;

public:
    ColCliente();
    void add(Cliente* i);
    void remove(Cliente* i);
    bool member(Cliente* i);
    bool isEmpty();
    ClienteIterator* getIterator();
};

#endif
