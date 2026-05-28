#include "ICollection/collections/List.h"
//IMPLEMENTACION DEL WRAPPER DE LA COLECCION DE USUARIOS

#include "ColUsuario.h"

ColUsuario::ColUsuario(){
    this->col = new List();
}

void ColUsuario::add(Usuario* i) {
    this->col->add(i); 
}

void ColUsuario::remove(Usuario* i){
    this->col->remove(i);
}

bool ColUsuario::member(Usuario* i){
    return this->col->member(i);
}

bool ColUsuario::isEmpty(){
    return this->col->isEmpty();
}

UsuarioIterator* ColUsuario::getIterator() { // CASTEO DEL OBJETO 
    return new UsuarioIterator(this->col->getIterator()); // ITERADOR GENERICO QUE DEVUELVE AL OBJETO CONCRETO
}