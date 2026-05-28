#ifndef USUARIOITERATOR_H
#define USUARIOITERATOR_H

#include "ICollection/interfaces/IIterator.h"
#include "Usuario.h"

class UsuarioIterator {
private:
    IIterator* iter;

public:
    UsuarioIterator(IIterator* iter);
    ~UsuarioIterator();

    Usuario* getCurrent();
    bool hasCurrent();
    void next();
};

#endif