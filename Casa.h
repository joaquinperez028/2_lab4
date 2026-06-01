#ifndef CASA_H
#define CASA_H
 
#include "Inmueble.h"
#include "Datatypes/DTEspecifica.h"  
#include "Datatypes/DTCasa.h"        
#include "Datatypes/TipoTecho.h"     
 
class Casa : public Inmueble {
private:
    tipoTecho techo;
    bool      propHorizontal;

public:
    Casa(direccion dir, float superficie, int identificador, tipoTecho techo, bool propHorizontal);

    bool getPropHorizontal() const;
    tipoTecho getTipoTecho() const;

    void crearCasa(direccion dir, float superficie, int identificador, tipoTecho techo, bool propHorizontal);
    void mostrarDetalle(int id) override;
};
 
#endif 