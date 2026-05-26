#ifndef APARTAMENTO_H
#define APARTAMENTO_H
 
#include "Inmueble.h"
#include "datatypes.h"
 
class Apartamento : public Inmueble {
private:
    int   numPiso;
    bool  ascensor;
    float gastosComunes;
 
public:
    Apartamento(direccion dir, float superficie, int identificador, int numPiso, bool ascensor, float gastosComunes);
 
    int   getNumPiso() const;
    bool  getAscensor() const;
    float getGastosComunes() const;
 
    void crearApto(direccion dir, float superficie, int identificador, int numPiso, bool ascensor, float gastosComunes);
    void mostrarDetalle(int id) override;
};
 
#endif 