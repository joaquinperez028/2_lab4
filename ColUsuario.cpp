
IMPLEMENTACION DEL WRAPPER DE LA COLECCION DE USUARIOS

#include "ColUsuario.h"
#include // ACA HAY QUE INCLUIR EL TIPO DE ESTRUCTURA QUE VAMOS A USAR, LISTA O ARBOL, ETC .H

ColUsuario::ColUsuario() {
    this->col = new //DE LISTA O ARBOL O ETC, LO QUE HAYAMOS ELEGIDO(); 
}

void ColUsuario::add(Usuario* i) {
    this->col->add(i); 
}

void ColUsuario::remove(Usuario* i){

}

bool ColUsuario::member(Usuario* i){

}

bool ColUsuario::isEmpty(){

}

UsuarioIterator* ColUsuario::getIterator() { // CASTEO DEL OBJETO 
    return new UsuarioIterator(this->col->getIterator()); // ITERADOR GENERICO QUE DEVUELVE AL OBJETO CONCRETO
}