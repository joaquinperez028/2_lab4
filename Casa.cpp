#include "Casa.h"
#include "Propietario.h"

// Constructor — delega los atributos comunes a Inmueble
Casa::Casa(direccion dir, float superficie, int identificador, TipoTecho tipoTecho, bool propHorizontal)
    : Inmueble(dir, superficie, identificador, tipoInmueble::Casa) {
    this->tipoTecho = tipoTecho;
    this->propHorizontal = propHorizontal;
}

// --- Getters ---

bool Casa::getPropHorizontal() const {
    return this->propHorizontal;
}

TipoTecho Casa::getTipoTecho() const {
    return this->tipoTecho;
}

// Factory method — crea una instancia de Casa
// Corresponde al crearCasa del DCD, llamado desde Propietario
void Casa::crearCasa(direccion dir, float superficie, int identificador, TipoTecho tipoTecho, bool propHorizontal) {
    this->direccion_ = dir;
    this->superficie = superficie;
    this->identificador = identificador;
    this->tipoTecho = tipoTecho;
    this->propHorizontal = propHorizontal;
}

// Implementacion del virtual puro de Inmueble
// Retorna un DTCasa con todos los datos especificos de la casa
// Corresponde al mensaje mostrarDetalle del diagrama
void Casa::mostrarDetalle(int id) {
    // se construye el DTCasa con los datos propios y heredados
    DTCasa* dt = new DTCasa(
        this->getSuperficie(),
        this->getDireccion(),
        this->getAnoConstruc(),
        tipoInmueble::Casa,
        this->tipoTecho,
        this->propHorizontal
    );
}

DTEspecifica* Casa::getInmueble() {
    return new DTCasa(
        this->getSuperficie(),
        this->getDireccion(),
        this->getAnoConstruc(),
        tipoInmueble::Casa,
        this->tipoTecho,
        this->propHorizontal
    );
}
