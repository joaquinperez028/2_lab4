#include "ColInmobiliaria.h"
//#include // ACA HAY QUE INCLUIR EL TIPO DE ESTRUCTURA QUE VAMOS A USAR, LISTA O ARBOL, ETC .H

ColInmobiliaria::ColInmobiliaria() {
    this->col = new //DE LISTA O ARBOL O ETC, LO QUE HAYAMOS ELEGIDO(); 
}

void ColInmobiliaria::add(Inmobiliaria* i) {
    this->col->add(i); 
}

void ColInmobiliaria::remove(Inmobiliaria* i){

}

bool ColInmobiliaria::member(Inmobiliaria* i){

}

bool ColInmobiliaria::isEmpty(){

}

IIterator* ColInmobiliaria::getIterator() { // CASTEO DEL OBJETO 
    return this->col->getIterator(); // ITERADOR GENERICO QUE DEVUELVE AL OBJETO CONCRETO
}