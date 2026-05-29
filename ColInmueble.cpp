
// IMPLEMENTACION DEL WRAPPER DE LA COLECCION DE INMUEBLES

#include "ColInmueble.h"
#include "ICollection/collections/List.h"

ColInmueble::ColInmueble() {
    this->col = new List();
}

void ColInmueble::add(Inmueble* i) {
    this->col->add(i); 
}

void ColInmueble::remove(Inmueble* i){
    this->col->remove(i);
}

bool ColInmueble::member(Inmueble* i){
    return this->col->member(i);
}

bool ColInmueble::isEmpty(){
    return this->col->isEmpty();
}

InmuebleIterator* ColInmueble::getIterator() { // CASTEO DEL OBJETO 
    return new InmuebleIterator(this->col->getIterator()); // ITERADOR GENERICO QUE DEVUELVE AL OBJETO CONCRETO
}