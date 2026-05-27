#ifndef INMUEBLE_H
#define INMUEBLE_H
 
#include <string>
#include "interfaces/ICollectible.h"
#include "datatypes/direccion.h"
using namespace std;

class Propietario;
 
class Inmueble : public ICollectible {
protected:
    direccion  direccion_;
    float      superficie;
    string     telefono;
    int        identificador;
 
    Propietario* propietario;
 
public:
    Inmueble(direccion dir, float superficie, string telefono, int identificador);
 
    direccion getDireccion() const;
    float getSuperficie() const;
    string getTelefono() const;
    int getIdentificador() const;
    Propietario* getPropietario() const;
 
    void asociarPropietario(Propietario* p);
    void listarPropiedades();
    virtual void mostrarDetalle(int id) = 0;
    void removerInmueble(Inmueble* inm);
};
 
#endif 