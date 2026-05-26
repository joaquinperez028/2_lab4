// IMPLEMENTACION DEL WRAPPER DE LA COLECCION DE CLIENTES

#include "ColCliente.h"
#include // ACA HAY QUE INCLUIR EL TIPO DE ESTRUCTURA QUE VAMOS A USAR, LISTA O ARBOL, ETC .H

ColCliente::ColCliente() {
    this->col = new //DE LISTA O ARBOL O ETC, LO QUE HAYAMOS ELEGIDO();
}

void ColCliente::add(Cliente* i) {
    this->col->add(i);
}

void ColCliente::remove(Cliente* i) {
}

bool ColCliente::member(Cliente* i) {
}

bool ColCliente::isEmpty() {
}

ClienteIterator* ColCliente::getIterator() { // CASTEO DEL OBJETO
    return new ClienteIterator(this->col->getIterator()); // ITERADOR GENERICO QUE DEVUELVE AL OBJETO CONCRETO
}
