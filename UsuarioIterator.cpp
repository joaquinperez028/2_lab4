#include "UsuarioIterator.h"

UsuarioIterator::UsuarioIterator(IIterator* iter) : iter(iter) {}

UsuarioIterator::~UsuarioIterator() {
    delete iter;
}

Usuario* UsuarioIterator::getCurrent() {
    return dynamic_cast<Usuario*>(iter->getCurrent());
}

bool UsuarioIterator::hasCurrent() {
    return iter->hasCurrent();
}

void UsuarioIterator::next() {
    iter->next();
}