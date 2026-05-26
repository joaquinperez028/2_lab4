#include "ColCasa.h"
#include 
ColCasa::ColCasa() {
    this->col = new //DE LISTA O ARBOL O ETC, LO QUE HAYAMOS ELEGIDO();
}
 
void ColCasa::add(Casa* i) {
    this->col->add(i);
}
 
void ColCasa::remove(Casa* i){
 
}
 
bool ColCasa::member(Casa* i){
 
}
 
bool ColCasa::isEmpty(){
 
}
 
CasaIterator* ColCasa::getIterator() {
    return new CasaIterator(this->col->getIterator()); // ITERADOR GENERICO QUE DEVUELVE AL OBJETO CONCRETO
}