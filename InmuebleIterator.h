#ifndef INMUEBLEITERATOR_H
#define INMUEBLEITERATOR_H

#include "ICollection/interfaces/IIterator.h"
#include "Inmueble.h"

class InmuebleIterator {
private:
    IIterator* iter;

public:
    InmuebleIterator(IIterator* iter);
    ~InmuebleIterator();

    Inmueble* getCurrent();
    bool hasCurrent();
    void next();
};

#endif