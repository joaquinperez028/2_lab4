#include "ColApartamento.h"

 
ColApartamento::ColApartamento() {
    this->col = new 
}
 
void ColApartamento::add(Apartamento* i) {
    this->col->add(i);
}
 
void ColApartamento::remove(Apartamento* i){
 
}
 
bool ColApartamento::member(Apartamento* i){
 
}
 
bool ColApartamento::isEmpty(){
 
}
 
IIterator* ColApartamento::getIterator() { 
    return this->col->getIterator(); 
}