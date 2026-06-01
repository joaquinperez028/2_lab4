#ifndef CASA_H
#define CASA_H
 
#include "Inmueble.h"
#include "Datatypes/DTEspecifica.h"  
#include "Datatypes/DTCasa.h"        
#include "Datatypes/TipoTecho.h"     
 
class Casa : public Inmueble {
private:
    TipoTecho tipoTecho;
    bool      propHorizontal;
 
public:
    Casa(direccion dir, float superficie, int identificador,TipoTecho tipoTecho, bool propHorizontal);
    
    bool getPropHorizontal() const;
    TipoTecho getTipoTecho() const;
 
    void crearCasa(direccion dir, float superficie, int identificador, TipoTecho tipoTecho, bool propHorizontal);
    void mostrarDetalle(int id) override;
    DTEspecifica* getInmueble() override;
};
 
#endif 