
// IMPLEMENTACION DEL WRAPPER DE LA COLECCION DE INMUEBLES

#include "ColInmueble.h"
//#include // ACA HAY QUE INCLUIR EL TIPO DE ESTRUCTURA QUE VAMOS A USAR, LISTA O ARBOL, ETC .H

ColInmueble::ColInmueble() {
    this->col = new //DE LISTA O ARBOL O ETC, LO QUE HAYAMOS ELEGIDO(); 
}

void ColInmueble::add(Inmueble* i) {
    this->col->add(i); 
}

void ColInmueble::remove(Inmueble* i){

}

bool ColInmueble::member(Inmueble* i){

}

bool ColInmueble::isEmpty(){

}

IIterator* ColInmueble::getIterator() { // CASTEO DEL OBJETO 
    return this->col->getIterator(); // ITERADOR GENERICO QUE DEVUELVE AL OBJETO CONCRETO
}