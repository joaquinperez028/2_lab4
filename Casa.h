#ifndef CASA_H
#define CASA_H
 
#include "Inmueble.h"
#include "datatypes/direccion.h"
#include "datatypes/tipoTecho.h"
 
class Casa : public Inmueble {
private:
    tipoTecho tipoTecho;
    bool      propHorizontal;
 
public:
    Casa(direccion dir, float superficie, int identificador,tipoTecho tipoTecho, bool propHorizontal);
    
    bool getPropHorizontal() const;
    tipoTecho gettipoTecho() const;
 
    void crearCasa(direccion dir, float superficie, int identificador, tipoTecho tipoTecho, bool propHorizontal);
    void mostrarDetalle(int id) override;
};
 
#endif 