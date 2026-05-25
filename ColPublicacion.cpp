// IMPLEMENTACION DEL WRAPPER DE LA COLECCION DE PUBLICACIONES

#include "ColPublicacion.h"
#include // ACA HAY QUE INCLUIR EL TIPO DE ESTRUCTURA QUE VAMOS A USAR, LISTA O ARBOL, ETC .H

ColPublicacion::ColPublicacion() {
    this->col = new //DE LISTA O ARBOL O ETC, LO QUE HAYAMOS ELEGIDO(); 
}

void ColPublicacion::add(Publicacion* i) {
    this->col->add(i); 
}

void ColPublicacion::remove(Publicacion* i){

}

bool ColPublicacion::member(Publicacion* i){

}

bool ColPublicacion::isEmpty(){

}

PublicacionIterator* ColPublicacion::getIterator() { // CASTEO DEL OBJETO 
    return new PublicacionIterator(this->col->getIterator()); // ITERADOR GENERICO QUE DEVUELVE AL OBJETO CONCRETO
}