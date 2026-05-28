#ifndef DTPUBLICACIONES_H
#define DTPUBLICACIONES_H

#include <string>
#include "Fecha.h"
#include "TipoPublicacion.h"
#include "TipoInmueble.h"

using namespace std;

class DTPublicaciones
{
private:
    bool activa;
    int codigoPubli;
    fecha fechaPubli;
    string textoDescriptivo;
    float precio;
    string nomInmo;
    tipoPublicacion tipoPublicacion;
    tipoInmueble tipoInmueble;

public:
    DTPublicaciones();
    DTPublicaciones(bool activa, int codigoPubli, fecha fechaPubli, string textoDescriptivo, float precio, string nomInmo, ::tipoPublicacion tipoPublicacion, ::tipoInmueble tipoInmueble);
    bool getActiva();
    int getCodigoPubli();
    fecha getFechaPubli();
    string getTextoDescriptivo();
    float getPrecio();
    string getNomInmo();
    ::tipoPublicacion getTipoPublicacion();
    ::tipoInmueble getTipoInmueble();
};

#endif
