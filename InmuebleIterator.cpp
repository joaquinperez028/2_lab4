#include "InmuebleIterator.h"

InmuebleIterator::InmuebleIterator(IIterator* iter) : iter(iter) {}

InmuebleIterator::~InmuebleIterator() {
    delete iter;
}

Inmueble* InmuebleIterator::getCurrent() {
    return dynamic_cast<Inmueble*>(iter->getCurrent());
}

bool InmuebleIterator::hasCurrent() {
    return iter->hasCurrent();
}

void InmuebleIterator::next() {
    iter->next();
}