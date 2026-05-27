// IMPLEMENTACION DEL WRAPPER DE LA COLECCION DE ADMINISTRA

#include "ColAdministra.h"
//#include // ACA HAY QUE INCLUIR EL TIPO DE ESTRUCTURA QUE VAMOS A USAR, LISTA O ARBOL, ETC .H

ColAdministra::ColAdministra() {
    this->col = new //DE LISTA O ARBOL O ETC, LO QUE HAYAMOS ELEGIDO(); 
}

void ColAdministra::add(Administra* i) {
    this->col->add(i); 
}

void ColAdministra::remove(Administra* i){

}

bool ColAdministra::member(Administra* i){

}

bool ColAdministra::isEmpty(){

}

IIterator* ColAdministra::getIterator() { // CASTEO DEL OBJETO 
    return this->col->getIterator(); // ITERADOR GENERICO QUE DEVUELVE AL OBJETO CONCRETO
}