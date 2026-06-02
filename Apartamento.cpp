#include "Apartamento.h"
#include "Propietario.h"

// Constructor — delega los atributos comunes a Inmueble
Apartamento::Apartamento(direccion dir, float superficie, int identificador, int numPiso, bool ascensor, float gastosComunes)
    : Inmueble(dir, superficie, identificador, tipoInmueble::Apartamento) {
    this->numPiso = numPiso;
    this->ascensor = ascensor;
    this->gastosComunes = gastosComunes;
}

// --- Getters ---

int Apartamento::getNumPiso() const {
    return this->numPiso;
}

bool Apartamento::getAscensor() const {
    return this->ascensor;
}

float Apartamento::getGastosComunes() const {
    return this->gastosComunes;
}

// Factory method — crea una instancia de Apartamento
// Corresponde al crearApto del DCD, llamado desde Propietario
void Apartamento::crearApto(direccion dir, float superficie, int identificador, int numPiso, bool ascensor, float gastosComunes) {
    this->direccion_ = dir;
    this->superficie = superficie;
    this->identificador = identificador;
    this->numPiso = numPiso;
    this->ascensor = ascensor;
    this->gastosComunes = gastosComunes;
}

// Implementacion del virtual puro de Inmueble
// Retorna un DTApartamento con todos los datos especificos del apartamento
// Corresponde al mensaje mostrarDetalle del diagrama
void Apartamento::mostrarDetalle(int id) {
    // se construye el DTApartamento con los datos propios y heredados
    DTApartamento* dt = new DTApartamento(
        this->getSuperficie(),
        this->getDireccion(),
        this->getAnoConstruc(),
        tipoInmueble::Apartamento,
        this->numPiso,
        this->ascensor,
        this->gastosComunes
    );
}

// Implementacion del virtual puro de Inmueble
// Apartamento construye un DTApartamento con todos sus datos
DTEspecifica* Apartamento::getInmueble() {
    return new DTApartamento(
        this->getSuperficie(),
        this->getDireccion(),
        this->getAnoConstruc(),
        tipoInmueble::Apartamento,
        this->numPiso,
        this->ascensor,
        this->gastosComunes
    );
}