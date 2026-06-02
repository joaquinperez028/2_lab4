#ifndef DTINMUEBLE_H
#define DTINMUEBLE_H
 
#include "Direccion.h"
#include "Fecha.h"
#include "TipoInmueble.h"
 
using namespace std;
 
class DTInmueble
{
private:
    int codigoInmueble;
    direccion direccion_;
    fecha anioConstrucion;
    tipoInmueble tipo;
 
public:
    DTInmueble();
    DTInmueble(int codigoInmueble, ::direccion direccion, fecha anioConstrucion, tipoInmueble tipo);
 
    int getCodigoInmueble();
    ::direccion getDireccion();
    fecha getAnioConstrucion();
    tipoInmueble getTipo();
};
 
#endif